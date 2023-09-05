#include <string.h>      /* strlen, memcpy              */
#include <stdio.h>       /* fopen, FILE. fclose, remove */
#include "buse_logger.h" /* Internal API                */
/*****************************************************************************/
static FILE *fd = NULL;
static char file_name[BUFSIZ] = {0};
/*****************************************************************************/
int NbdCreateLog(const char *log_name)
{
    size_t size = strlen(log_name) + 1;
    fd = fopen(log_name, "w");
    if(NULL == fd)
    {
        return -1;
    }

    memcpy(file_name, log_name, size);
    file_name[size] = '\0';
    fclose(fd);
    return 0;
}
/*****************************************************************************/
void NbdLog(const char *msg, int data)
{
    fd = fopen(file_name, "a+");
    if(fd)
    {
        if(data)
            fprintf(fd, "%s %d\n", msg, data);
        else
            fprintf(fd, "%s\n", msg);
        fclose(fd);
    }
}
/*****************************************************************************/
void NbdClearLog(void)
{
    fd = fopen(file_name, "w");
    if(fd)
    {
        fclose(fd);
    }
}
/*****************************************************************************/
void NbdPrintLog(void)
{
    char buffer[BUFSIZ] = {0};
    fd = fopen(file_name, "r");
    if(fd)
    {
        while(NULL != fgets(buffer, sizeof(buffer), fd))
        {
            fputs(buffer, stdout);
        }

        fclose(fd);
    }
}
/*****************************************************************************/