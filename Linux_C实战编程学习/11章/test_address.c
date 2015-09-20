/*************************************************************************
	> File Name: test_address.c
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年08月02日 星期日 14时27分31秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
    char buffer[40];
    int ret = 0;
    int host = 0;
    int network = 0;
    unsigned int address = 0;

    struct in_addr in;

    in.s_addr = 0;

    printf("please input your ip address:");
    fgets(buffer, 39, stdin);
    //这里我们输入分别输入172.17.242.131和255.255.255.255
    buffer[39] = '\0';
    /*
     * inet_aton(const char *cp , struct in_addr *inp)
     * 将参数cp所指向的字符串形式的IP地址转换为二进制的网络字节顺序的IP地址
     * 存于inp所指向的空间中.成功返回非0值,参数无效返回0
     * 输出结果:0x83f211ac /  0xffffffff
     */
    if((ret = inet_aton(buffer, &in)) == 0){
        printf("inet_aton: \t invalid address\n");
    }
    else{
        printf("inet_atom:\t 0x%x\n", in.s_addr);
    }
    /*
     * inet_addr(const char *cp)
     * 将参数cp所指向的字符串形式的网络地址转换为网络字节顺序形式的二进制IP地址
     * 执行成功的结果返回,参数无效返回-1
     * 输出结果:0x83f211ac /  invalid adress
     * 因为考虑到255.255.255.255的就是-1的补码,所以导致出错,这是一个非常容易出错的地方
     */
    if((address = inet_addr(buffer)) == INADDR_NONE){
        printf("inet_addr: \t invalid address\n");
    }
    else{
        printf("inet_addr:\t0x%lx\n", address);
    }
    /*
     * inet_network(const char *buf)
     * 将参数cp所指向的字符串形式的网络地址转换为主机字节顺序形式的二进制IP地址
     * 直系那个成功返回结果,参数无效返回-1
     * 输出结果:0xac11f283 /  invalid adress
     * 输出原因同上
     */
    if((address = inet_network(buffer)) == -1){
        printf("inet_network: \t invalid address\n");
    }
    else{
        printf("inet_network:\t0x%lx\n", address);
    }
    /*
     * inet_ntoa(struct in_addr in)
     * 该函数将值为in的网络字节顺序形式的二进制IP地址转换成为以.为分隔的字符串形式
     * 执行成功返回结果字符串的指针,参数无效返回NULL
     * 输出结果:172.17.242.131 /  255.255.255.255
     */
    if(inet_ntoa(in) == NULL){
        printf("inet_ntoa: \t invalid adress\n");
    }
    else{
        printf("inet_ntoa:\t%s\n", inet_ntoa(in));
    }
    /*
     * inet_lnaof(struct in_addr in)
     * 该函数从参数in中提取出主机地址,执行成功返回主机字节顺序形式的主机地址.
     * 如172.17.242.131,属于B类地址,则主机号为低16位,主机地址为0.0.242.131,按主机字节顺序输出为下:
     * 输出结果:0xf283 /  0xff
     */
    host =inet_lnaof(in);
    /*inet_netof(struct in_addr in)
     * 该函数从参数in中提取出网络地址,执行成功返回主机字节顺序形式的网络地址.
     * 与上例对应即网络地址为高16位的172.17.0.0
     * 输出结果:0xac11  / 0xffffff
     */
    network = inet_netof(in);
    printf("inet_lnaof:\t0x%x\n", host);
    printf("inet_netof:\t0x%x\n", network);
    /*
     * inet_makeaddr(int net, int host)
     * 该函数将网络号为参数net,主机号为host的两个地址组合成为一个网络地址
     * 输出结果:0x83f211ac  / 0xffffffff
     */
    in = inet_makeaddr(network, host);
    printf("inet_makeaddr:0x%x\n", in.s_addr);

    return 0;
}
