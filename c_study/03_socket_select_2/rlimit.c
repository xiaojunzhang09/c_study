//
// Created by rust on 2025/11/16.
//
#include <stdio.h>      // 添加这行 - 用于 perror
#include <stdlib.h>     // 添加这行 - 用于 exit
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <secure/_string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/errno.h>

#define ERR_EXIT(m) \
do \
{   \
    perror(m);  \
    exit(EXIT_FAILURE); \
}while(0)

int main(void) {
    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0 ) {
        ERR_EXIT("getrlimit");
    }

    printf("%d\n",(int) rl.rlim_max);

    rl.rlim_cur = 2048;
    rl.rlim_max = 2048;
    if (setrlimit(RLIMIT_NOFILE, &rl) < 0 ) {
        ERR_EXIT("setrlimit");
    }

    if (getrlimit(RLIMIT_NOFILE, &rl) < 0 ) {
        ERR_EXIT("getrlimit");
    }

    printf("%d\n",(int) rl.rlim_max);

    printf("%d\n",(int) rl.rlim_max);


    return 0;
}