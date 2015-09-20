/*************************************************************************
	> File Name: my_recv.h
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年08月03日 星期一 15时08分30秒
 ************************************************************************/

#ifndef _MY_RECV_H
#define _MY_RECV_H
    #define BUFSIZE 1024
    void my_err(const char *err_string, int line);
    int my_recv(int conn_fd, char *data_buf, int len);
#endif
