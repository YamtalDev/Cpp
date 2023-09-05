/******************************************************************************

    Writer: Tal Aharon

    Reviewer: .

    Date: 28.08.2023


******************************************************************************/
#define _POSIX_C_SOURCE (200809L)
#include <sys/ioctl.h>   /* ioctl                                           */
#include <stdio.h>       /* BUFSIZ                                          */
#include <string.h>      /* memcpy                                          */
#include <unistd.h>      /* fork, close                                     */
#include <stdlib.h>      /* calloc, free                                    */
#include <fcntl.h>       /* O_RDWR, open                                    */
#include <netinet/in.h>  /* socketpair, SOCKET_STREAM, AF_LOCAL             */
#include <signal.h>      /* sigset_t, sigfillset, sigprocmask, SIG_SETMASK  */ 

#include <linux/nbd.h>   /* NBD_SET_SIZE, NBD_DO_IT, NBD_CLEAR_SOCK         */
                         /* NBD_CLEAR_QUE, NBD_SET_SOCK,                    */

#include "buse.h"        /* Internal API                                    */
#include <buse_logger.h> /* Internal API                                    */
/*****************************************************************************/
#ifdef WORDS_BIGENDIAN
u_int64_t ntohll(u_int64_t a)
{
    return a;
}
#else
u_int64_t ntohll(u_int64_t a)
{
    u_int32_t hi = (a >> 32U);
    u_int32_t lo = (a & 0xffffffff);
    lo = ntohl(lo), hi = ntohl(hi);
    return (((u_int64_t)lo) << 32U | hi);
}
#endif
#define htonll ntohll
/*****************************************************************************/
enum buse_status
{
    BUSE_FAILURE = -1, BUSE_SUCCESS
};

typedef struct nbd_reply buse_reply_t;
typedef struct nbd_buse_request
{
    buse_request_t req;
    buse_reply_t rep;
    char data[1];

} nbd_buse_request_t;
static int32_t nbd_dev = -1;
/*****************************************************************************/
static void NbdDisconnect(int32_t);
static void SetSignalHandlers(void);
static void BlockDriverSignals(void);
static void NbdCleanUp(int32_t, int32_t *);
static void NbdClearDriver(int32_t, int32_t *);
static ssize_t ReadRequest(int32_t, int8_t *, size_t);
static ssize_t WriteReply(int32_t, int8_t *, size_t);
static int32_t NbdConfigure(int32_t *, const char *, size_t);
static int32_t SetSigaction(int32_t, const struct sigaction *);
static int32_t NbdFillRequest(int32_t, nbd_buse_request_t *, struct nbd_request *);
/******************************************************************************
 * @brief NbdOpen: Set driver and socket, activate driver in a child process.
 * @param device_name: the nbd kernel device from the user machine. 
 * @param m_size Number of bytes to set on the block device. 
 * @return -1 for failure, Socket descriptor to the driver.
 * @return DRIVER_EXIT_STATUS - driver process finished, return success to caller in this case.
******************************************************************************/
int NbdOpen(const char *device_name, size_t m_size)
{
    pid_t pid = 0;
    int32_t nbd_dev = 0;
    int32_t nbd_sockets[2] = {0};

    #ifdef BUSE_DEBUG
    if(0 != NbdCreateLog("buse.log"))
        return (1);
    #endif

    nbd_dev = NbdConfigure(nbd_sockets, device_name, m_size);
    if(-1 == nbd_dev)
    {
        #ifdef BUSE_DEBUG
        NbdLog("NbdOpen: Set up failed", __LINE__);
        #endif

        NbdCleanUp(nbd_dev, nbd_sockets);
        return (BUSE_FAILURE);
    }

    pid = fork();
    if(-1 == pid)
    {
        #ifdef BUSE_DEBUG
        NbdLog("NbdOpen: Forking the driver failed", __LINE__);

        #endif
        NbdCleanUp(nbd_dev, nbd_sockets);
        return (BUSE_FAILURE);
    }
    else if(0 == pid)
    {
        close(nbd_sockets[0]);
        BlockDriverSignals();
        if((-1 == ioctl(nbd_dev, NBD_SET_SOCK, nbd_sockets[1])) ||
           (-1 == ioctl(nbd_dev, NBD_DO_IT)))
        {
            #ifdef BUSE_DEBUG
            NbdLog("NbdOpen: Driver is taken", __LINE__);
            #endif

            NbdCleanUp(nbd_dev, nbd_sockets);
            return (BUSE_FAILURE);
        }

        NbdClearDriver(nbd_dev, nbd_sockets);
        #ifdef BUSE_DEBUG
        NbdLog("Driver exit successfully.", 0);
        #endif

        return (DRIVER_EXIT_STATUS);
    }

    SetSignalHandlers();
    close(nbd_sockets[1]);
    return (nbd_sockets[0]);
}
/******************************************************************************
 * @brief NbdGetRequest: handle a request from driver and read/write data to it.
 * @param nbd_socket: nbd socket file descriptor to read and write to the driver.
 * @return Pointer to a request structure defined in the user buse.h header.
******************************************************************************/
buse_request_t *NbdGetRequest(int32_t nbd_socket)
{
    size_t request_size = 0;
    nbd_buse_request_t *request = NULL;
    struct nbd_request sys_req;

    if(0 > ReadRequest(nbd_socket, (int8_t *)&sys_req, sizeof(sys_req)))
    {
        #ifdef BUSE_DEBUG
        NbdLog("File system request error", __LINE__);
        #endif

        return (NULL);
    }

    /* Maybe using malloc is more efficient. Garbage values not important? */
    request_size = sizeof(nbd_buse_request_t) + ntohl(sys_req.len) - 1;
    request = (nbd_buse_request_t *)calloc(request_size, sizeof(int8_t));
    if(NULL == request)
    {
        #ifdef BUSE_DEBUG
        NbdLog("Allocation failure of request", __LINE__);
        #endif

        return (NULL);
    }

    if(-1 == NbdFillRequest(nbd_socket, request, &sys_req))
    {
        #ifdef BUSE_DEBUG
        NbdLog("Request fill failure", __LINE__);
        #endif

        free(request);
        return (NULL);
    }

    return ((buse_request_t *)request);
}
/******************************************************************************
 * @brief NbdRequestDone: send a respond to the sender, also handles read requests.
 * @param nbd_socket socket file descriptor to communicate with the driver.
 * @param request request structure returned from get request function.
 * @return 0 for success and -1 for failure.
*******************************************************************************/
int NbdRequestDone(int nbd_socket, buse_request_t *request)
{
    int32_t status = BUSE_SUCCESS;
    int32_t read = (BUSE_CMD_READ == request->type);
    buse_reply_t *reply = &(((nbd_buse_request_t *)request)->rep);
    size_t reply_size = read * request->len + sizeof(buse_reply_t);
    status = -1 * (0 > WriteReply(nbd_socket, (int8_t *)reply, reply_size));

    #ifdef BUSE_DEBUG
    NbdLog("Read request Bytes", request->len);
    #endif

    free(request);
    request = NULL;
    return (status);
}
/******************************************************************************
 * @brief Utility function to clean up the request structure if needed.
 * @param request request structure returned from get request function.
******************************************************************************/
void NbdDestroyRequest(buse_request_t *request)
{
    free(request);
    request = NULL;
}
/*****************************************************************************/
static int32_t NbdFillRequest
(int32_t fd, nbd_buse_request_t *request, struct nbd_request *sys_req)
{
    int32_t write = 0;
    request->req.data = request->data;
    request->req.len = ntohl(sys_req->len);
    request->req.type = ntohl(sys_req->type);
    request->req.from = ntohll(sys_req->from);

    request->rep.error = htonl(0);
    request->rep.magic = htonl(NBD_REPLY_MAGIC);
    memcpy(request->rep.handle, sys_req->handle, sizeof(sys_req->handle));

    /* Evaluate if writing to the data buffer is needed */
    write = (BUSE_CMD_WRITE == request->req.type);

    #ifdef BUSE_DEBUG
    if(write)
        NbdLog("Write request Bytes", request->req.len);
    #endif

    return (-1 * (write && (0 > ReadRequest(fd, (int8_t *)request->data, request->req.len))));
}
/*****************************************************************************/
static ssize_t ReadRequest(int32_t fd, int8_t *buf, size_t n)
{
    ssize_t bytes_read = 0;
    while(0 <= bytes_read && n > 0)
    {
        bytes_read = recv(fd, buf, n, 0);
        buf += bytes_read;
        n -= bytes_read;
    }

    return (bytes_read);
}
/*****************************************************************************/
static ssize_t WriteReply(int32_t fd, int8_t *buf, size_t n)
{
    ssize_t bytes_sent = 0;
    while(0 <= bytes_sent && n > 0)
    {
        bytes_sent = send(fd, buf, n, 0);
        buf += bytes_sent;
        n -= bytes_sent;
    }

    return (bytes_sent);
}
/*****************************************************************************/
static void NbdCleanUp(int32_t nbd, int32_t *nbd_sockets)
{
    close(nbd);
    close(nbd_sockets[0]);
    close(nbd_sockets[1]);
}
/*****************************************************************************/
static void BlockDriverSignals(void)
{
    sigset_t sigset = {0};
    if(0 != sigfillset(&sigset) || 0 != sigprocmask(SIG_SETMASK, &sigset, NULL))
    {
        #ifdef BUSE_DEBUG
        NbdLog("Set driver signal mask failed", __LINE__);
        #endif
    }
}
/*****************************************************************************/
static void SetSignalHandlers(void)
{
    int32_t status = 0;
    struct sigaction act;
    act.sa_flags = SA_RESTART;
    act.sa_handler = NbdDisconnect;
    status += 0 != sigemptyset(&act.sa_mask);
    status += 0 != sigaddset(&act.sa_mask, SIGINT);
    status += 0 != sigaddset(&act.sa_mask, SIGTERM);
    status += 0 != SetSigaction(SIGINT, &act);
    status += 0 != SetSigaction(SIGTERM, &act);
    if(status)
    {
        #ifdef BUSE_DEBUG
        NbdLog("Failed to prepare signal masking", __LINE__);
        #endif
    }
}
/*****************************************************************************/
static int32_t SetSigaction(int32_t sig, const struct sigaction *act)
{
    struct sigaction o_act;
    return (0 == sigaction(sig, act, &o_act)  && o_act.sa_handler != SIG_DFL);
}
/*****************************************************************************/
static void NbdDisconnect(int32_t signal)
{
    (void)signal;
    if(-1 != nbd_dev)
    {
        ioctl(nbd_dev, NBD_DISCONNECT);
        close(nbd_dev);
        nbd_dev = -1;

        #ifdef BUSE_DEBUG
        NbdLog("Successfully disconnected from device.", 0);
        #endif
    }
}
/*****************************************************************************/
static void NbdClearDriver(int32_t nbd, int32_t *nbd_sockets)
{
    ioctl(nbd, NBD_CLEAR_QUE);
    ioctl(nbd, NBD_CLEAR_SOCK);
    NbdCleanUp(nbd, nbd_sockets);
    ioctl(nbd_dev, NBD_DISCONNECT);

    #ifdef BUSE_DEBUG
    NbdLog("Clearing driver and disconnecting.", 0);
    #endif
}
/*****************************************************************************/
static int32_t NbdConfigure
(int32_t *nbd_sockets, const char *device_name, size_t m_size)
{
    int32_t nbd = 0;
    if(-1 == socketpair(AF_UNIX, SOCK_STREAM, 0, nbd_sockets))
    {
        #ifdef BUSE_DEBUG
        NbdLog("Socket pair failure", __LINE__);
        #endif

        return (BUSE_FAILURE);
    }

    /* opening the device and configuring */
    nbd = open(device_name, O_RDWR);
    if((-1 == nbd) || (-1 == ioctl(nbd, NBD_SET_SIZE, m_size))  ||
       (-1 == ioctl(nbd, NBD_CLEAR_SOCK)))
    {
        #ifdef BUSE_DEBUG
        NbdLog("Open, set size or clear socket failure", __LINE__);
        #endif

        return (BUSE_FAILURE);
    }

    return (nbd);
}
/*****************************************************************************/
