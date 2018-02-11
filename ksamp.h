#ifndef _KSAMP_H_
#define _KSAMP_H_

#define MAX_BUF_LEN 500 //should be big enough?
#define TRUE 1
#define debug 0

int main(int, char **);
void usage(void);
void defaultUse(void);
void lInfo(int, int);
void sInfo(void);
void usage(void);
char *getSubStr(const char *, const char *);
char *getEntry(int, const char *, const char *);
void freeDefault(void);
void freeS(void);
void freeL(void);

#endif
