/******************************************************************************

    Writer: Tal Aharon

    Reviewer: First name and family name.

    Date: 28.08.2023

*******************************************************************************

                          Description:

  

******************************************************************************/
#include <stdio.h>       /* puts                 */ 
#include <string.h>      /* memcpy               */
#include <stdlib.h>      /* calloc, free         */
#include <netinet/in.h>  /* u_int32_t, u_int64_t */
#include <sys/select.h>  /* select  */
#include <time.h>        /* time_t, time         */
#include <unistd.h>      /*  */
#include <signal.h>      /* raise, SIGTERM       */

#include "buse.h"        /* Internal API         */
#include <buse_logger.h> /* Internal API         */
/*****************************************************************************/
#define RUNNING (1)
#define STOP_RUNNING (0)
#define MB (1 << 20)
static int InputRequest(void);
static int32_t NbdServer(void);
static int FailureNCleanUp(void *);
static void SetTimeOut(struct timeval *);
static int HandleRequest(buse_request_t *, void *);
static void ReadRequest(void *, void *, u_int32_t, u_int64_t);
static void WriteRequest(const void *, void *, u_int32_t, u_int64_t);
/*****************************************************************************/
int main(void)
{
    int status = 0;
    if(-1 == NbdServer())
    {
        status = 1;
    }

    return (status);
}
/*****************************************************************************/
static int32_t NbdServer(void)
{
    int32_t max_fd = 0;
    int32_t sock_fd = 0;
    void *buffer = NULL;
    int32_t ready_fd = 0;
    fd_set read_fds = {0};
    struct timeval timeout = {0};
    time_t start_time = time(NULL);
    buse_request_t *request = NULL;
    int32_t server = RUNNING;

    sock_fd = NbdOpen("/dev/nbd0", 512 * MB);
    if(-1 == sock_fd)
    {
        return (sock_fd);
    }
    else if(DRIVER_EXIT_STATUS == sock_fd)
    {
        return (0);
    }

    buffer = calloc((512 * MB), sizeof(char));
    if(NULL == buffer)
    {
        return (-1);
    }

    max_fd = (sock_fd > STDIN_FILENO) ? sock_fd : STDIN_FILENO;
    while(RUNNING == server)
    {
        FD_ZERO(&read_fds);
        FD_SET(sock_fd, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        SetTimeOut(&timeout);
        ready_fd = select(max_fd + 1, &read_fds, NULL, NULL, &timeout);
        if(ready_fd == -1)
        {
            #ifdef BUSE_DEBUG
            NbdLog("Select failed", __LINE__);
            #endif
            return (FailureNCleanUp(buffer));
        }
        else if(ready_fd == 0)
        {
            #ifdef BUSE_DEBUG
            NbdLog("No activity in server, [sec] passed:", time(NULL) - start_time);
            #endif
        }

        if(0 < ready_fd && FD_ISSET(sock_fd, &read_fds))
        {
            request = NbdGetRequest(sock_fd);
            if(request == NULL)
                return (FailureNCleanUp(buffer));

            server = HandleRequest(request, buffer);
            if(RUNNING == server && 0 != NbdRequestDone(sock_fd, request))
                return (FailureNCleanUp(buffer));
        }

        if(0 < ready_fd && FD_ISSET(STDIN_FILENO, &read_fds))
        {
            server = InputRequest();
        }

        FD_CLR(sock_fd, &read_fds);
        FD_CLR(STDIN_FILENO, &read_fds);
    }

    return (!FailureNCleanUp(buffer));
}
/*****************************************************************************/
static void ReadRequest(void *buf, void *data,u_int32_t len, u_int64_t offset)
{
    memcpy(buf, (char *)data + offset, len);
}
/*****************************************************************************/
static void WriteRequest(const void *buf, void *data, u_int32_t len, u_int64_t offset)
{
    memcpy((char *)data + offset, buf, len);
}
/*****************************************************************************/
static int HandleRequest(buse_request_t *request, void *buffer)
{
    int status = RUNNING;
    switch(request->type)
    {

    case (BUSE_CMD_READ):

        ReadRequest(request->data, buffer, request->len, request->from);
        break;

    case (BUSE_CMD_WRITE):

        WriteRequest(request->data, buffer, request->len, request->from);
        break;

    case (BUSE_CMD_DISC):

        #ifdef BUSE_DEBUG
        NbdLog("Got disconnection request.", 0);
        #endif

        raise(SIGTERM);
        NbdDestroyRequest(request);
        status = STOP_RUNNING;
        break;

    case (BUSE_CMD_FLUSH):

        #ifdef BUSE_DEBUG
        NbdLog("Got flush request.", 0);
        #endif

        break;

    case (BUSE_CMD_TRIM):

        #ifdef BUSE_DEBUG
        NbdLog("Got flush request.", 0);
        #endif

        break;

    default:

        break;

    }

    return (status);
}
/*****************************************************************************/
static int InputRequest(void)
{
    char buffer[BUFSIZ] = {0};
    if(-1 == read(STDIN_FILENO, buffer, BUFSIZ))
    {
        #ifdef BUSE_DEBUG
        NbdLog("Read Input request failure.", 0);
        #endif
        return (STOP_RUNNING);
    }

    if(0 == strcmp(buffer, "quit\n"))
    {
        #ifdef BUSE_DEBUG
        NbdLog("Stop server request accepted.", 0);
        #endif
        raise(SIGTERM);
        return (STOP_RUNNING);
    }

    if(0 == strcmp(buffer, "-info\n"))
    {
        #ifdef BUSE_DEBUG
        NbdPrintLog();
        #else
        puts("Info is available in debugging mode");
        #endif
    }
    else
    {
        system(buffer);
    }

    return (RUNNING);
}
/*****************************************************************************/
static void SetTimeOut(struct timeval *timeout)
{
    timeout->tv_sec = 15;
    timeout->tv_usec = 0;
}
/*****************************************************************************/
static int FailureNCleanUp(void *buffer)
{
    free(buffer);
    return (-1);
}
/*****************************************************************************/
