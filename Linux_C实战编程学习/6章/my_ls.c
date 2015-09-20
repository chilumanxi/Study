/*************************************************************************
    > File Name: my_ls.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com
    > Created Time: 2015年07月20日 星期一 14时37分06秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <dirent.h>
#define PARAM_NONE 0
#define PARAM_a 1    //-a 显示所有文件
#define PARAM_l 2    //-l 一行只显示一个文件的详细信息
#define PARAM_c 4    //-c 按照文件最后修改时间顺序输出
#define PARAM_i 8    //-i 打印含inode结点信息的文件名
#define PARAM_S 16	 //-S 按照文件大小排序
#define PARAM_s 32   //-s 输出文件大小信息和文件名
#define PARAM_R 64   //-R 递归展开文件夹中内容
#define MAXROWLEN 160 //一行显示的最多字符数
void display_detail(struct stat buf, char *name);
void display_single(int flag_command, char *name, struct stat buf);
void display(int flag, char *pathname);
void display(int flag_command, char *path);
int g_leave_len = MAXROWLEN; //一行剩余长度
int g_maxlen = 0;                //目录下最长的文件名的长度
int size_maxlen = 0;             //目录下最大的文件大小的长度
int size_all = 0;
int flag = 0;
void my_err(const char *err_string, int line){
	fprintf(stderr, "lint : %d  ", line);
	perror(err_string);
	exit(1);
}

int  check(int x){
	int ans = 0;
	x = x/4097 * 4 + 4;
	while(x != 0){
		x /= 10;
		ans ++;
	}
	return ans;
}

void display_detail(struct stat buf, char *name){
	char buf_time[40];
	struct passwd *npasswd;
	struct group *ngroup;
    //文件类型的判断
	if(S_ISLNK(buf.st_mode)){
		printf("l");
	}
	else if(S_ISREG(buf.st_mode)){
		printf("-");
	}
	else if(S_ISDIR(buf.st_mode)){
		printf("d");
	}
	else if(S_ISCHR(buf.st_mode)){
		printf("c");
	}
	else if(S_ISBLK(buf.st_mode)){
		printf("b");
	}
	else if(S_ISFIFO(buf.st_mode)){
		printf("f");
	}
	else if(S_ISSOCK(buf.st_mode)){
		printf("s");
	}

	//文件所属用户的权限
	if(buf.st_mode & S_IRUSR){
		printf("r");
	}
	else
		printf("-");
	if(buf.st_mode & S_IWUSR){
		printf("w");
	}
	else
		printf("-");
	if(buf.st_mode & S_IXUSR){
		printf("x");
	}
	else
		printf("-");

	//同一用户组的权限
	if(buf.st_mode & S_IRGRP){
		printf("r");
	}
	else
		printf("-");
	if(buf.st_mode & S_IWGRP){
		printf("w");
	}
	else
		printf("-");
	if(buf.st_mode & S_IXGRP){
		printf("x");
	}
	else
		printf("-");

	//其他用户的权限
	if(buf.st_mode & S_IROTH){
		printf("r");
	}
	else
		printf("-");
	if(buf.st_mode & S_IWOTH){
		printf("w");
	}
	else
		printf("-");
	if(buf.st_mode & S_IXOTH){
		printf("x");
	}
	else
		printf("-");

	printf(" ");

	npasswd = getpwuid(buf.st_uid);
	ngroup = getgrgid(buf.st_gid);

	//打印文件的链接数目
	printf("%4d ", buf.st_nlink);

	//打印文件所属用户和组名
	printf("%-8s", npasswd -> pw_name);
	printf("%-8s", ngroup -> gr_name);

	//打印文件的}大小
	printf("%6d ", buf.st_size);

	//打印文件的时间信息
	strcpy(buf_time, ctime(&buf.st_mtime));
	buf_time[strlen(buf_time) - 1] = '\0';     //去掉结尾的换行符
	printf("%s",buf_time);

}

void display_single(int flag_command,char *name, struct stat buf){
	int i, len;
	if(flag_command & PARAM_s){
		if(g_leave_len < g_maxlen + size_maxlen){
			printf("\n");
			g_leave_len = MAXROWLEN;
		}
		len = strlen(name);
		len = g_maxlen - len;
		for(i = 0; i < size_maxlen - check(buf.st_size); i++)
			printf(" ");
		if(buf.st_size == 0)
			printf("%d", buf.st_size);
		else {
			printf("%d", buf.st_size/4097 * 4 + 4);
		}
		if(S_ISDIR(buf.st_mode))
			printf(" \033[;36m%-s\033[0m", name);
		else if(buf.st_mode & S_IXUSR)
			printf(" \033[;32m%-s\033[0m", name);
		else 
			printf(" %-s",name);
		for(i = 0; i < len; i ++){
			printf(" ");
		}
	}
	else if(flag_command & PARAM_i){
		if(g_leave_len < g_maxlen + 7){
			printf("\n");
			g_leave_len = MAXROWLEN;
		}
		len = strlen(name);
		len = g_maxlen - len;
		printf("%-d", buf.st_ino);
		printf(" ");
		if(S_ISDIR(buf.st_mode))
			printf("\033[;36m%-s\033[0m", name);
		else if(buf.st_mode & S_IXUSR)
			printf("\033[;32m%-s\033[0m", name);
		else 
			printf("%-s",name);
		for(i = 0; i < len; i ++)
			printf(" ");
	}
	else{
		//如果本行剩余已经不够打印一行的话换行。
		if(g_leave_len < g_maxlen){
			printf("\n");
			g_leave_len = MAXROWLEN;
		}
		len = strlen(name);
		len = g_maxlen - len;
		if(S_ISDIR(buf.st_mode))
			printf("\033[;36m%-s\033[0m", name);
		else if(buf.st_mode & S_IXUSR)
			printf("\033[;32m%-s\033[0m", name);
		else printf("%-s",name);

		for(i = 0; i < len; i ++){
			printf(" ");
		}
	}
	//在文件名之间相差两个空格
	printf("  ");
	g_leave_len -= (g_maxlen + 2);
}

/*根据命令行参数和完整的路径名显示目标文件。
 * flag :命令行参数
 * pathname: 包含了文件名的路径名
 */

void display(int flag, char *pathname){
	int i, j;
	struct stat buf;
	char name[NAME_MAX + 1];   //NAME_MAX  255
	for(i = 0, j = 0; i < strlen(pathname); i ++){
		if(pathname[i] == '/'){
			j = 0;
			continue;
		}
		name[j ++] = pathname[i];
	}
	name[j] = '\0';

	if(lstat(pathname, &buf) == -1){
		my_err("stat", __LINE__);
	}
	if(pathname[0] == '0')
		return ;
	switch(flag){
		case PARAM_NONE:
			if(name[0] != '.' && name[1] != '/'){
				display_single(flag, name, buf);
			}
			break;
		case PARAM_a:
			display_single(flag, name, buf);
			break;
		case PARAM_l:
			if(name[0] != '.'){
				display_detail(buf, name);
				printf(" %-s\n", name);
			}
			break;
		case PARAM_c:
			if(name[0] != '.'){
				display_single(flag, name, buf);
			}
			break;
		case PARAM_i:
				display_single(flag, name, buf);
			
			break;
		case PARAM_s:
			if(name[0] != '.'){
				display_single(flag, name, buf);
			}
			break;
		case PARAM_S:
			if(name[0] != '.'){
				display_single(flag, name, buf);
			}
			break;
		case PARAM_R:
			if(name[0] != '.'){
				display_single(flag, name, buf);
			}
			break;
		case PARAM_a + PARAM_l:
			display_detail(buf, name);
			printf(" %-s\n", name);
			break;
		default :
			break;
	}
}
void display_recursion(char *pathname){
	int i, j, k, len = strlen(pathname);
	DIR *dir;
	struct dirent *ptr;
	int count = 0;
	struct stat buf[255];
	char  filenames[255][PATH_MAX + 1];
	char temp[PATH_MAX + 1];
	if((dir = opendir(pathname)) == NULL){
		my_err("opendir", __LINE__);
	}
	while((ptr = readdir(dir)) != NULL){
		if(g_maxlen < strlen(ptr -> d_name))
			g_maxlen = strlen(ptr -> d_name);
		count ++;
	}
	closedir(dir);
	if(count >= 1000000){
		my_err("too many files under this dir", __LINE__);
	}

	dir = opendir(pathname);
	for(i = 0; i < count; i ++){
		ptr = readdir(dir);
		if(ptr == NULL)
			my_err("readdir", __LINE__);
		strncpy(filenames[i], pathname, len);
		filenames[i][len] = '\0';
		strcat(filenames[i], ptr -> d_name);
		filenames[i][len + strlen(ptr -> d_name)] = '\0';
		if(lstat(filenames[i], &buf[i]) == -1)
			my_err("lstat", __LINE__);
	}
/*
		if(S_ISDIR(buf[i].st_mode) && filenames[i][strlen(filenames[i]) - 1] != '.'){
			k = strlen(filenames[i]);
			filenames[i][k] = '/';
			filenames[i][k + 1] = '\0';
			display_recursion(filenames[i]);
		}
		else if(S_ISDIR(buf[i].st_mode) && filenames[i][strlen(filenames[i]) - 1] == '.' ){
			if(flag == 0){
				printf("%s:\n", pathname);
				flag = 1;
			}
			display(64, filenames[i]);
		}
	}
	printf("%s:\n", pathname);
	for(i = 0; i < count; i ++){
		if(filenames[i][strlen(filenames[i] - 2)] != '.')
			display(64, filenames[i]);
	}
	*/
	if(flag == 0 && pathname[strlen(pathname) - 1] == '.'){
		printf("%s:\n", "pathname");
		for(i = 0; i < count; i ++){
			display(64, filenames[i]);
		}
		flag = 1;
		printf("\n");
	}
	else{
		printf("%s:\n", pathname);
		for(i = 0; i < count; i ++)
			display(64, filenames[i]);
		printf("\n");
	}
	for(i = 0; i < count; i ++){
		k = strlen(filenames[i]);
		if(S_ISDIR(buf[i].st_mode) && filenames[i][k -1] != '.'){
			filenames[i][k] = '/';
			filenames[i][k + 1] = '\0';			
			display_recursion(filenames[i]);
		}
	}
	closedir(dir);

}
void display_dir(int flag_command, char *path){
	int i , j, k, len = strlen(path);
	DIR *dir;
	struct dirent *ptr;
	int count = 0;
	struct stat buf[256];
	char filenames[256][PATH_MAX + 1];
	char temp[PATH_MAX + 1];
	int temp_te;

	if((dir = opendir(path)) == NULL){
		my_err("opendir", __LINE__);
	}
	while((ptr = readdir(dir)) != NULL){
		if(g_maxlen < strlen(ptr -> d_name))
			g_maxlen = strlen(ptr -> d_name);
		count ++;
	}
	closedir(dir);
	if(count >= 256){
		my_err("too many files under this dir", __LINE__);
	}

	dir = opendir(path);
	for(i = 0; i < count; i ++){
		ptr = readdir(dir);
		if(ptr == NULL)
			my_err("readdir", __LINE__);
		strncpy(filenames[i], path, len);
		filenames[i][len] = '\0';
		strcat(filenames[i], ptr -> d_name);
		filenames[i][len + strlen(ptr -> d_name)] = '\0';
	}
	
	if(flag_command & PARAM_c){
		for(i = 0; i < count - 1; i ++){
			stat(filenames[i], &buf[i]);
		}
		for(i = 0; i < count - 1; i ++){
			for(j = 0; j < i; j ++){
				if(buf[j].st_ctime < buf[j + 1].st_ctime){
					strcpy(temp, filenames[j + 1]);
					temp[strlen(filenames[j + 1])] = '\0';
					strcpy(filenames[j + 1], filenames[j]);
					filenames[j + 1][strlen(filenames[j])] = '\0';
					strcpy(filenames[j], temp);
					filenames[j][strlen(temp)] = '\0';
					stat(filenames[j], &buf[j]); 	
					stat(filenames[j + 1], &buf[j + 1]); 			
				}				
			}
		}
		
			
	}
	else if(flag_command & PARAM_S){
		for(i = 0; i < count - 1; i ++){
			stat(filenames[i], &buf[i]);
		}
		for(i = 0; i < count - 1; i ++){
			for(j = 0; j < i; j ++){
				if(buf[j].st_size < buf[j + 1].st_size){
					strcpy(temp, filenames[j + 1]);
					temp[strlen(filenames[j + 1])] = '\0';
					strcpy(filenames[j + 1], filenames[j]);
					filenames[j + 1][strlen(filenames[j])] = '\0';
					strcpy(filenames[j], temp);
					filenames[j][strlen(temp)] = '\0';
					stat(filenames[j], &buf[j]); 	
					stat(filenames[j + 1], &buf[j + 1]); 			
				}				
			}
		}
	}
		
	else {
		for(i = 0; i < count - 1; i ++){
			stat(filenames[i], &buf[i]);
			if(buf[i].st_size > 0)
				size_all += (buf[i].st_size / 4097 * 4 + 4);
			if(size_maxlen < check(buf[i].st_size))
				size_maxlen = check(buf[i].st_size);
			for(j = 0; j < i; j ++){
				if(strcmp(filenames[j], filenames[j + 1]) > 0){
					strcpy(temp, filenames[j + 1]);
					temp[strlen(filenames[j + 1])] = '\0';
					strcpy(filenames[j + 1], filenames[j]);
					filenames[j + 1][strlen(filenames[j])] = '\0';
					strcpy(filenames[j], temp);
					filenames[j][strlen(temp)] = '\0';
				}
			}
		}
	}
	if(flag_command & PARAM_s)
		printf("总用量 %d\n", size_all);
	for(i = 0; i < count; i ++){
		display(flag_command, filenames[i]);
	}

	closedir(dir);

	if((flag_command & PARAM_l) == 0)
		printf("\n");
}


int main(int argc, char **argv){
	int i = 0, j = 0, k = 0, num = 0;
	char path[PATH_MAX + 1];
	char command[40];
	int flag_command = PARAM_NONE;
	struct stat buf;


	for(i = 1; i < argc; i ++){
		if(argv[i][0] == '-'){
			for(k = 1; k < strlen(argv[i]); k ++, j ++){
				command[j] = argv[i][k];
			}
			num ++;
		}
	}

	for(i = 0; i < j; i ++){
		if(command[i] == 'a'){
			flag_command |= PARAM_a;
			continue;
		}
		else if(command[i] == 'l'){
			flag_command |= PARAM_l;
			continue;
		}
		else if(command[i] == 'c'){
			flag_command |= PARAM_c;
		}
		else if(command[i] == 'i'){
			flag_command |= PARAM_i;
		}
		else if(command[i] == 's'){
			flag_command |= PARAM_s;
		}
		else if(command[i] == 'S'){
			flag_command |= PARAM_S;
		}
		else if(command[i] == 'R'){
			flag_command |= PARAM_R;
		}
		else {
			printf("my_ls invalid option -%c\n", command[i]);
			exit(1);
		}
	}
	command[j] = '\0';

	//如果没有输入目标文件或者目录，就显示当前目录
	if((num + 1) == argc){
		strcpy(path, "./");
		path[2] = '\0';
		display_dir(flag_command, path);
		return 0;
	}
	
	i = 1;
	do{
		if(argv[i][0] == '-'){
			i ++;
			continue;
		}
		else {
			strcpy(path, argv[i]);
			if(stat(path, &buf) < 0){
				my_err("stat", __LINE__);
			}
			else if(S_ISDIR(buf.st_mode) ){
				if(strcmp(path, ".") == 0){
					path[1] = '/';
					path[2] = '\0';
				}
				else if(path[strlen(argv[i]) - 1] != '/'){
					path[strlen(argv[i] - 1)] = '/';
					path[strlen(argv[i])] = '\0';
				}
				else path[strlen(argv[i])] = '\0';
				if(flag_command & PARAM_R)
					display_recursion(path);
				else 
					display_dir(flag_command, path);
				i ++;
			}
			else {
				display(flag_command, path);
				i ++;
			}
		}

	}while(i < argc);



	return 0;
}

