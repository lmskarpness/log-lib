#ifndef LOG
#define LOG

#include <time.h>

typedef struct data_struct {
    char *time;
    char *string;
} data_t;

int addmsg(data_t data);
void clearlog(void);
char *getlog(void);
int savelog(char *filename);

#endif