/*************************************************************************
    > File Name: fcntl_lock.c
    > Author: zhanghaoran
    > Mail: 467908670@qq.com 
    > Created Time: 2015年05月28日 星期四 16时32分41秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
void my_err(const char *err_string, int line){
	fprintf(stderr, "line:%d  ",line);
	perror(err_string);
	exit(1);
}

//锁的设置或释放函数

int lock_set(int fd, struct flock * lock){
	if (fcntl(fd, F_SETLK, lock) == 0){
		if(lock -> l_type == F_RDLCK)
			printf("set read lock, pid:%d\n", getpid());
		else if(lock -> l_type == F_WRLCK)
			printf("set write lock, pid:%d\n",getpid());
		else if(lock -> l_type == F_UNLCK)
			printf("release lock,pid:%d\n",getpid());
	}
	else {
		printf("lock opertation fail\n");
		return -1;
	}
	return 0;
}

//测试锁,只有当测试锁发现参数lock指定的锁能被设置时,返回0
int lock_test(int fd, struct flock *lock){
	if(fcntl(fd, F_GETLK, lock ) == 0){
		if(lock -> l_type == F_UNLCK){
			printf("look can be set in fd\n");
			return 0;
		}
		else{  //有不兼容的锁的存在,打印出设置锁的的进程ID
			if(lock -> l_type == F_RDLCK)
				printf("can't set lock, read lock has been set by :%d\n", lock -> l_pid);
			else if(lock -> l_type == F_WRLCK)
				printf("can't set lock, write lock has been set by :%d\n", lock -> l_pid );
			return -2;
		}
	}
	else {
		perror("get incompatible locks fail");
		return -1;
	}
}


int main(){
	int fd;
	int ret;
	struct flock lock;
	char read_buf[20];
	
	//打开或创建文件
	if((fd = open("example_65", O_CREAT|O_TRUNC|O_RDWR, S_IRWXU)) == -1){
		my_err("open", __LINE__);
	}
	if(write(fd, "test_lock", 10) != 10){
		my_err("write", __LINE__);
	}

	memset(&lock, 0, sizeof(struct flock));
	lock.l_start = SEEK_SET;
	lock.l_whence = 0;
	lock.l_len = 0;

	//设置读锁
	lock.l_type = F_RDLCK;
	if(lock_test(fd, &lock) == 0){  //测试可以设置锁
		lock.l_type = F_RDLCK;
		lock_set(fd, &lock);
	}

	//读数据
	lseek(fd, 0, SEEK_SET);
	if((ret = read(fd, read_buf, 10)) < 0){
		my_err("read", __LINE__);
	}
	read_buf[ret] = '\0';
	printf("%s\n",read_buf);

	getchar();

	//设置写锁
	lock.l_type = F_WRLCK;
	if(lock_test(fd, &lock) == 0){
		lock.l_type = F_WRLCK;
		lock_set(fd, &lock);
	}

	//释放锁
	lock.l_type = F_UNLCK;
	lock_set(fd, &lock);
	close(fd);
	return 0;
}

