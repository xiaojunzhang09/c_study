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

// struct packet {
//     int len;
//     char buf[1024];
// };

ssize_t readn(int fd, void *buf, size_t count) {
    size_t nleft = count; //剩余字节数
    ssize_t nread; //实际读取的字节数

    char *bufp = (char *) buf;
    while (nleft > 0) {
        if ((nread = read(fd, bufp, nleft)) < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                return -1;
            }
        } else if (nread == 0) {
            return count - nleft; // 返回实际读取的字节数
        }

        bufp += nread;
        nleft -= nread;
    }

    return count;
}


ssize_t writen(int fd, void *buf, size_t count) {
    size_t nleft = count; //剩余要发送的字节数
    ssize_t nwritten; //实际写入的字节数

    char *bufp = (char *) buf;
    while (nleft > 0) {
        if ((nwritten = write(fd, bufp, nleft)) < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                return -1;
            }
        } else if (nwritten == 0) {
            continue;
        }

        bufp += nwritten;
        nleft -= nwritten;
    }

    return count;
}

ssize_t recv_peek(int sockfd, void *buf, size_t len) {
    while (1) {
        int ret = recv(sockfd, buf, len,MSG_PEEK); //最好减少系统调用
        if (ret == -1 && errno == EINTR) {
            /* Interrupted system call */
            continue;
        }
        return ret;
    }
}

ssize_t readline(int sockfd, void *buf, size_t maxLine) {
    int ret;
    int nread;
    char *bufp = buf;
    int nleft = maxLine;

    while (1) {
        ret = recv_peek(sockfd, bufp, nleft);
        if (ret < 0) {
            //失败
            return ret;
        } else if (ret == 0) {
            //对端关闭了 套节字接口
            return ret;
        }
        nread = ret; //接受到的字节数
        int i;
        for (i = 0; i < nread; i++) {
            if (bufp[i] == '\n') {
                ret = readn(sockfd, bufp, i + 1);
                if (ret != i + 1) {
                    exit(EXIT_FAILURE);
                }
                return ret;
            }
        }
        if (nread > nleft) {
            exit(EXIT_FAILURE);
        }

        nleft -= nread;
        ret = readn(sockfd, bufp, nread);
        if (ret != nread) {
            exit(EXIT_FAILURE);
        }
        bufp += nread;
    }
    return -1;
}

void echo_srv(int conn) {
    // 数据收发缓冲区
    char recvbuf[1024];
    // 循环读取客户端数据并回传给客户端
    while (1) {
        memset(recvbuf, 0, sizeof(recvbuf)); // 清空缓冲区
        //1. 先接收4个字节
        int ret = readline(conn, recvbuf, 1024); // 从连接中读取数据
        if (ret == -1) {
            ERR_EXIT("readline");
        }
        if (ret == 0) {
            printf("client close\n");
            break;
        }

        // printf("%s", recvbuf);                          // 将接收到的内容输出到标准输出（注意格式可能存在问题）
        fputs(recvbuf,stdout);
        writen(conn, recvbuf, strlen(recvbuf)); // 回传相同数据给客户端
    }
}


int main(void) {
    int listenfd;

    // 创建TCP套接字
    //((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) // 0 自动选择协议
    if ((listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        ERR_EXIT("socket");
    }

    // 初始化服务器地址结构体
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET; // 设置地址族为IPv4
    servaddr.sin_port = htons(5188); // 设置监听端口号为5188

    // 设置IP地址为INADDR_ANY，表示绑定本机任意可用IP地址
    //1.
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //2.
    //servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //3.
    //inet_aton("127.0.0.1",&servaddr.sin_addr);

    int on = 1;
    if ((setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR, &on, sizeof(on))) < 0) {
        ERR_EXIT("setsockopt");
    }


    // 绑定套接字与服务器地址
    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        ERR_EXIT("bind");
    }

    // 开始监听连接请求，最大连接队列为系统允许的最大值
    if (listen(listenfd, SOMAXCONN) < 0) {
        ERR_EXIT("listen");
    }

    // 存储客户端地址信息及长度
    struct sockaddr_in peeraddr;
    socklen_t peerlen = sizeof(peeraddr); //一定要初始化，否则会失败

    //已链接套接字 :主动套接字
    // 接受客户端连接请求，建立新的已连接套接字
    int conn;
    pid_t pid;
    while (1) {
        if ((conn = accept(listenfd, (struct sockaddr *) &peeraddr, &peerlen)) < 0) {
            ERR_EXIT("accept");
        }

        printf("ip = %s port = %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

        //创建1个进程
        pid = fork();
        if (pid == -1) {
            ERR_EXIT("fork");
        }
        if (pid == 0) {
            //父进程不需要监听
            close(listenfd);
            echo_srv(conn);
            exit(EXIT_SUCCESS);
        } else {
            //子进程不需要关注链接
            close(conn);
        }
    }


    return 0;
}
