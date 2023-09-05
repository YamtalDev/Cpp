#ifndef __BUSE_H__
#define __BUSE_H__

#include <stddef.h> /* size_t             */
#include <stdint.h> /* uint64_t, uint32_t */
#define DRIVER_EXIT_STATUS (-2)

typedef enum buse_command
{
    BUSE_CMD_READ,
    BUSE_CMD_WRITE,
    BUSE_CMD_DISC,
    BUSE_CMD_FLUSH,
    BUSE_CMD_TRIM

} buse_command_t;

typedef struct buse_request
{
    uint64_t from;
    char *data;
    int32_t len;
    buse_command_t type;

} buse_request_t;

/******************************************************************************
 * @brief NbdOpen: Set driver and socket, activate driver in a child process.
 * @param device_name: the nbd kernel device from the user machine. 
 * @param m_size Number of bytes to set on the block device. 
 * @return -1 for failure, Socket descriptor to the driver.
 * @return DRIVER_EXIT_STATUS - driver process finished, return success to caller in this case.
 *****************************************************************************/
int NbdOpen(const char *file_name, size_t size_in_bytes);

/******************************************************************************
 * @brief NbdGetRequest: handle a request from driver and read/write data to it. 
 * @param nbd_socket: nbd socket file descriptor to read and write to the driver.  
 * @return Pointer to a request structure defined in the user buse.h header.
 *****************************************************************************/
buse_request_t *NbdGetRequest(int nbd_socket);

/******************************************************************************
 * @brief NbdRequestDone: send a respond to the sender, also handles read requests.
 * @param nbd_socket socket file descriptor to communicate with the driver.
 * @param request request structure returned from get request function.
 * @return 0 for success and -1 for failure.
 *****************************************************************************/
int NbdRequestDone(int nbd_socket, buse_request_t *request);

/******************************************************************************
 * @brief Utility function to clean up the request structure if needed.
 * @param request request structure returned from get request function.
******************************************************************************/
void NbdDestroyRequest(buse_request_t *request);

#endif /* __BUSE_H__*/