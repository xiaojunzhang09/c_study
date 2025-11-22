//
// Created by rust on 2025/11/16.
//

// 包含必要的头文件
#include <stdio.h>      // 用于 perror, fgets, fputs 等标准输入输出函数
#include <stdlib.h>     // 用于 exit 函数
#include <string.h>     // 用于 memset, strlen 等字符串操作函数
#include <arpa/inet.h>  // 用于 htons, inet_addr 等网络地址转换函数
#include <netinet/in.h> // 用于 sockaddr_in 结构体
#include <secure/_string.h> // macOS/iOS 安全字符串函数
#include <sys/socket.h> // 用于 socket, connect, read, write 等套接字函数
#include <unistd.h>     // 用于 close, read, write 等系统调用

/**
 * 错误处理宏定义
 * 当系统调用失败时，打印错误信息并退出程序
 * @param m 错误信息字符串
 */
#define ERR_EXIT(m) \
do \
{   \
    perror(m); \
    exit(EXIT_FAILURE); \
}while(0)

/**
 * 主函数 - TCP客户端程序入口
 * 实现与服务器建立连接，发送用户输入并接收回显数据的功能
 */
int main(void) {
    int sock; // 声明客户端套接字描述符

    // 创建TCP套接字
    // PF_INET: 协议族为IPv4
    // SOCK_STREAM: 流式套接字(TCP)
    // IPPROTO_TCP: 使用TCP协议
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        ERR_EXIT("socket"); // 套接字创建失败时输出错误并退出
    }

    // 初始化服务器地址结构体
    struct sockaddr_in servaddr; // 声明服务器地址结构体
    memset(&servaddr, 0, sizeof(servaddr)); // 将结构体清零初始化

    // 配置服务器地址信息
    servaddr.sin_family = AF_INET; // 设置地址族为IPv4
    servaddr.sin_port = htons(5188); // 设置端口号为5188，htons用于网络字节序转换

    // 设置服务器IP地址为127.0.0.1(本地回环地址)
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 向服务器发起连接请求
    // connect函数尝试与指定地址的服务器建立连接
    if (connect(sock, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        ERR_EXIT("connect"); // 连接失败时输出错误并退出
    }

    // 声明发送和接收缓冲区
    char sendbuf[1024] = {0}; // 发送缓冲区，初始化为0
    char recvbuf[1024] = {0}; // 接收缓冲区，初始化为0

    // 主循环：读取用户输入，发送给服务器，接收并显示回显数据
    // fgets从标准输入(stdin)读取一行数据到sendbuf中
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) {
        // 将用户输入的数据通过套接字发送给服务器
        // strlen获取实际输入长度，避免发送多余的空字符
        write(sock, sendbuf, strlen(sendbuf));

        // 从套接字读取服务器回显的数据
        read(sock, recvbuf, sizeof(recvbuf));

        // 将接收到的数据输出到标准输出(stdout)
        fputs(recvbuf, stdout);

        // 清空缓冲区，为下次循环做准备
        memset(sendbuf, 0, sizeof(sendbuf)); // 清空发送缓冲区
        memset(recvbuf, 0, sizeof(recvbuf)); // 清空接收缓冲区
    }

    // 关闭套接字，释放资源
    close(sock);

    return 0; // 正常退出程序
}
