#include <stdio.h>
#include <sys/_endian.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// #include <netinet/in.h>
// #include <arpa/inet.h>
// int inet_aton(const char *cp, struct in_addr *inp);
// in_addr_t inet_addr(const char *cp);
// char *inet_ntoa(struct in_addr in);

int main(void) {
    /**
    这段代码演示了主机字节序与网络字节序的转换：
    1. 定义32位整数x=0x12345678，按字节访问并打印其内存存储顺序
    2. 使用htonl()将x转换为网络字节序（大端序），结果存入y
    3. 再次按字节访问y并打印，展示字节序转换效果
    通过对比两次输出，可以直观看到主机字节序与网络字节序的差异。
     */
    unsigned int x = 0x12345678;
    unsigned char *p = (unsigned char*) &x;
    printf("%0x_%0x_%0x_%0x\n",p[0],p[1],p[2],p[3]);

    unsigned int y = htonl(x); // convert to network byte order
    p = (unsigned char*) &y;
    printf("%0x_%0x_%0x_%0x\n",p[0],p[1],p[2],p[3]);



    // 将点分十进制IP地址字符串转换为网络字节序的32位整数
    // inet_addr函数将"192.168.1.1"转换为网络字节序格式
    unsigned long addr = inet_addr("192.168.1.1");

    // 将网络字节序的32位整数转换为主机字节序并打印
    // ntohl函数执行网络字节序到主机字节序的转换
    printf("addr=%d\n",ntohl(addr));
    // 打印网络字节序的32位整数,无符号
    printf("addr=%u\n",ntohl(addr));



    struct in_addr ipaddr;                    /* 定义IPv4地址结构体变量 */
    ipaddr.s_addr = inet_addr("192.168.1.2"); /* 将点分十进制IP地址字符串转换为网络字节序的二进制格式 */
    printf("ipaddr=%s\n",inet_ntoa(ipaddr));  /* 将网络字节序的IP地址转换回点分十进制字符串并打印输出 */

    return 0;
}
