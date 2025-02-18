#include <stdio.h>
#include <string.h>

int main(void)
{
    const char buf_write[] = "hollo word\r\n";
    char buf_read[30] = "\0";
    FILE *f = NULL;
    int re = 0;

    f = fopen("./scr.txt", "w+");
    if (f == NULL)
    {
        perror("fopen error");
        fclose(f);
        return -1;
    }

    re = fwrite(buf_write, 1, strlen(buf_write), f);
    if (re < strlen(buf_write))
    {
        printf("fwrite error\r\n");
        fclose(f);
        return -1;
    }

    re = ftell(f);
    if (re == -1)
    {
        perror("ftell error");
        fclose(f);
        return -1;
    }
    printf("%d\r\n", re);

    re = fseek(f, 0, SEEK_SET);
    if (re == -1)
    {
        perror("fseek error");
        fclose(f);
        return -1;
    }

    re = fread(buf_read, 1, strlen(buf_write), f);
    if (re < strlen(buf_write))
    {
        if (feof(f) != 0)
        {
            printf("end of file\r\n");
            clearerr(f);
            fclose(f);
            return -1;
        }
        else if (ferror(f) != 0)
        {
            printf("fread error\r\n");
            clearerr(f);
            fclose(f);
            return -1;
        }
    }
    printf("%s\r\n", buf_read);
    fclose(f);

    return 0;
}