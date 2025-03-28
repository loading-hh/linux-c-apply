#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define SIGNAL 0
#define SIGACTION 1
void int_handler(int sig);
void error_return(sig_t fd, const char *buf, sig_t re);
int main(void)
{
#if SIGNAL

    sig_t ret = NULL;

    ret = signal(SIGINT, int_handler);
    error_return(ret, "signal error", SIG_ERR);

    while (1)
        ;
#endif

#if SIGACTION

    struct sigaction sig = {0};
    int re;

    sig.sa_handler = int_handler;
    sig.sa_flags = 0;
    re = sigaction(SIGINT, &sig, NULL);
    if (re == -1)
    {
        perror("sigaction error");
        return -1;
    }
    while (1)
        ;

#endif
    return 0;
}

void int_handler(int sig)
{
    printf("\r\n收到信号 %d\r\n", sig);
}

void error_return(sig_t fd, const char *buf, sig_t re)
{
    if (fd == re)
    {
        perror(buf);
        // close(fd);
        exit(-1);
    }
}