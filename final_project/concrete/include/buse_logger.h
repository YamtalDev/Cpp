#ifndef __BUSE_LOGGER_H__
#define __BUSE_LOGGER_H__

void NbdClearLog(void);
void NbdPrintLog(void);
void NbdLog(const char *msg, int data);
int NbdCreateLog(const char *log_name);

#endif /* __BUSE_H__*/
