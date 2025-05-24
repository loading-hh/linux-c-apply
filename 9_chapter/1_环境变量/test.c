#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ALLENV 1
#define SETENV 0
#define UNSETENV 0
extern char **environ;
void error_return(int re, const char *buf, int judge);
int main(int argc, char *argv[])
{
#if ALLENV
    for (int i = 0; environ[i] != NULL; i++)
        printf("%s\r\n", environ[i]);
#endif // ALLENV

#if SETENV

    int re = 0;
    char *ret = NULL;
    if (argc < 3)
    {
        printf("argc值不足\r\n");
        return -1;
    }
    re = setenv(argv[1], argv[2], 0);
    error_return(re, "setenv error", 0);

    ret = getenv(argv[1]);
    if (ret == NULL)
    {
        printf("没有名为%s的环境变量\r\n", argv[1]);
        return -1;
    }
    printf("环境变量%s的值为%s\r\n", argv[1], argv[2]);

#if UNSETENV
    re = unsetenv(argv[1]);
    error_return(re, "unserenv error", 0);

    ret = getenv(argv[1]);
    if (ret == NULL)
    {
        printf("没有名为%s的环境变量\r\n", argv[1]);
        return -1;
    }
    printf("环境变量%s的值为%s\r\n", argv[1], argv[2]);

#endif // UNSETENV

#endif // SETENV
    return 0;
}

void error_return(int re, const char *buf, int judge)
{
    if (re != judge)
    {
        perror(buf);
        // close(fd);
        exit(-1);
    }
}