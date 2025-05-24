#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void sig_handler(int sig);
int main(int argc, char *argv[])
{
    struct sigaction sig = {0};
    char *arg_arr[3];
    char *envp[3] = {"name=loading", "age=hh", NULL};

    arg_arr[0] = argv[1];
    arg_arr[1] = "Hello World";
    arg_arr[2] = NULL;
    sigemptyset(&sig.sa_mask);
    sig.sa_handler = sig_handler;
    sig.sa_flags = 0;
    if (sigaction(SIGCHLD, &sig, NULL) == -1)
    {
        printf("sigaction error\r\n");
        return -1;
    }

    switch (fork())
    {
    case -1:
        printf("fork error\r\n");
        return -1;
    case 0:
        printf("创建子进程 %d \r\n", getpid());
        if (execve(argv[1], arg_arr, envp) == -1)
            printf("execve error\r\n");
        return 0;
    default:
        break;
    }

    sleep(3);
    return 0;
}

void sig_handler(int sig)
{
    printf("回收子进程\r\n");
    while (waitpid(-1, NULL, WNOHANG) > 0)
        continue;
}