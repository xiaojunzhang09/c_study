//
// Created by rust on 2025/11/16.
//
#include <stdio.h>      // 添加这行 - 用于 perror
#include <stdlib.h>     // 添加这行 - 用于 exit
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>      // 添加这行 - 用于 gethostbyname
#include <string.h>

#define ERR_EXIT(m) \
do \
{   \
    perror(m);  \
    exit(EXIT_FAILURE); \
}while(0)

int getlocalip(char * ip) {
    char host[100] = {0};
    if (gethostname(host, sizeof(host)) < 0) {
        return -1;
    }
    struct hostent *hp;
    if ((hp = gethostbyname(host)) == NULL) {
        return -1;
    }

    // strcpy(ip,inet_ntoa(*(struct in_addr *)hp->h_addr_list[ 0 ]) );
    strcpy(ip,inet_ntoa(*(struct in_addr *)hp-> h_addr) );

    return 0;

}

int main(void) {
    char host[100] = {0};
    if (gethostname(host, sizeof(host)) < 0) {
        ERR_EXIT("gethostname");
    }

    struct hostent *hp;
    if ((hp = gethostbyname(host)) == NULL) {
        ERR_EXIT("gethostbyname");
    }

    int i = 0; //没有初始化，则值是随机的
    while (hp->h_addr_list[i] != NULL) {
        printf("%s\n",inet_ntoa(*(struct in_addr *)hp->h_addr_list[i]));
        i++;
    }

    char ip[16] = {0};
    getlocalip(ip);

    printf("localip = %s\n",ip);

    return 0;
}
