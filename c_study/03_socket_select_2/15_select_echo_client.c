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
    int count = 0;
   while (1) {
       int sock;
       if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
          // sleep(4);//休眠4秒 推迟close
           ERR_EXIT("socket");
       }
       struct sockaddr_in servaddr;
       memset(&servaddr, 0, sizeof(servaddr));

       servaddr.sin_family = AF_INET;
       servaddr.sin_port = htons(5188);
       servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

       if (connect(sock, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
           ERR_EXIT("connect");
       }
       struct  sockaddr_in localaddr;
       socklen_t addrlen = sizeof(localaddr);
       if (getsockname(sock, (struct sockaddr *) &localaddr, &addrlen) < 0) {
           ERR_EXIT("getsockname");
       }
       printf("ip = %s port = %d\n", inet_ntoa(localaddr.sin_addr), ntohs(localaddr.sin_port));
       printf("count = %d\n", ++count);
   }
    return 0;
}