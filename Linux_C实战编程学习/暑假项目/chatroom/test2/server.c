#include"server.h"

void load_info()
{
	FILE* fp;
	struct info* node;

	if((fp = fopen("client_info", "rb+")) == NULL)
	{
		perror("client_info not exist");
		return;
	}
	
	do
	{
		node = malloc(sizeof(struct info));
		node->next = NULL;
		if(fread(node, sizeof(struct info), 1, fp) ==1)
		{
			node->next = file_info;
			file_info = node;
		}
		else if(feof(fp))
			break;
		else
		{
			perror("read file error");
			exit(1);
		}
	}while(1);
	fclose(fp);
}

inline void init_client(fd_addr client[])
{
	int i;
	for(i=0; i<MAXPEOPLE; i++)
	{
		client[i].fd = -1;
		memset(client[i].user_name, 0, NAMELEN);
		client[i].in_room_flag = 0;
	}
}

void server()
{
	int sock_fd = -1;
	struct sockaddr_in my_addr;
	int addr_len = 0;
	int c_nums = 0; 
	int opt = 1;
	int len = sizeof(opt);
	pthread_t thread_id;

	init_client(client);
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(SERVPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 8);
	addr_len = sizeof(struct sockaddr_in);

	if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, len);
	if(bind(sock_fd, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1)
	{
		perror("bind");
		exit(1);
	}

	if(listen(sock_fd, BACKLOG) == -1)
	{
		perror("listen");
		exit(1);
	}

	while(1)
	{
		if((client[c_nums].fd = accept(sock_fd, 
						(struct sockaddr*)&client[c_nums].addr,
						&addr_len)) == -1)
		{
			perror("accept");
			continue;
		}

#ifdef DEBUG_VERSION
		printf("received a connection from %s\nfd:%d\nc_nums:%d\n", 
				inet_ntoa(client[c_nums].addr.sin_addr), 
				client[c_nums].fd, c_nums);
#endif

		pthread_create(&thread_id, NULL, &msg_processor, (void*)&client[c_nums]);

		c_nums = (c_nums+1)%MAXPEOPLE;
	}
	close(sock_fd);
}

void* msg_processor(void* parameter)
{
	fd_set readfds;
	char buf[BUFLEN] = {0};
	int numbytes = 0;

	fd_addr* client_p = (fd_addr*)parameter;

	if(!login(client_p))
		return;

	FD_ZERO(&readfds);
	while(1)
	{
		write(client_p->fd, "\n\t*********************************\n", BUFLEN);
		write(client_p->fd,   "\t* (1) Going to chatroom		*\n", BUFLEN);
		write(client_p->fd,   "\t* (2) Going to private chat	*\n", BUFLEN);
		write(client_p->fd,   "\t* (3) Exit			*\n", BUFLEN);
		write(client_p->fd,   "\t*********************************\n", BUFLEN);


		FD_SET(client_p->fd, &readfds);
		select((client_p->fd) + 1, &readfds, NULL, NULL, NULL);
		if(FD_ISSET(client_p->fd, &readfds))
		{
			memset(buf, 0, BUFLEN);
			if((numbytes = recv(client_p->fd, buf, BUFLEN, 0)) == 1)
			{
				perror("recv in send_all_user");
				close(client_p->fd);
				return;
			}
			buf[--numbytes] = '\0';  //buf recv have '\n'
#ifdef DEBUG_VERSION
			printf("recv:%s\n",buf);
#endif
	
			if(strlen(buf) != 1)
			{
				write(buf, "select error!!!\n", BUFLEN);
				sleep(1);
				continue;
			}

			if(buf[0] == '1')
			{
				printf("%s add to room\n", inet_ntoa(client_p->addr.sin_addr));
				sendto_all(">>>>>>>>>>>>>>come in>>>>>>>>>>>>>", client_p);
				write(client_p->fd,"\t---------------------------------\n",BUFLEN);
				write(client_p->fd,"\t*	Welcome to chatroom	*\n",BUFLEN);
				write(client_p->fd,"\t*Input \"Quit\" or \"quit\" to quit *\n",BUFLEN);
				write(client_p->fd,"\t---------------------------------\n",BUFLEN);

				client_p->in_room_flag = 1;
				chat_with_all(client_p);
			}

			else if(buf[0] == '2')
			{
				//TODO SEND TO A USER
				//......
				//chat_with_one(client_p, );
				write(client_p->fd, "this service is in building...\n", BUFLEN);
				sleep(1);
				//chat_with_one(client_p);
			}
			else if(buf[0] == '3')
			{
				write(client_p->fd, "EXIT", BUFLEN);
				close(client_p->fd);
				FD_ADDR_CLR(client_p);
				return NULL;
			}
		}

		FD_CLR(client_p->fd, &readfds);
	}
	close(client_p->fd);
	FD_ADDR_CLR(client_p);
	return NULL ;
}

int login(fd_addr* client_p)
{
	char buf[BUFLEN];
	int numbytes = 0;
	struct info* pnode;
	char tempname[NAMELEN];
	char temppwd[PWDLEN];
	int i;

	pnode = file_info;
	while(1)
	{
		write(client_p->fd, "\n\t*****************\n", BUFLEN);
		write(client_p->fd,   "\t* (1) Login	*\n", BUFLEN);
		write(client_p->fd,   "\t* (2) Regist	*\n", BUFLEN);
		write(client_p->fd,   "\t* (3) Exit	*\n", BUFLEN);
		write(client_p->fd,   "\t*****************\n", BUFLEN);

		memset(buf, 0, BUFLEN);
		if((numbytes = recv(client_p->fd, buf, BUFLEN, 0)) == -1)
		{
			perror("recv in login");
			pthread_exit(NULL);
		}
		buf[--numbytes] = '\0';
#ifdef DEBUG_VERSION
		printf("from:%s :%s\n", inet_ntoa(client_p->addr.sin_addr), buf);
#endif

		if(strlen(buf) != 1)  
			continue;
		
		//going to login
		if(buf[0] == '1')
		{
			write(client_p->fd, "\n\tinput you user name:\n", BUFLEN);
			memset(buf, 0, BUFLEN);
			if((numbytes = recv(client_p->fd, buf, BUFLEN, 0)) == -1)
			{
				perror("recv in login");
				pthread_exit(NULL);
			}
			buf[--numbytes] = '\0';
			strcpy(tempname, buf);	

			pnode = file_info;
			while(pnode)
			{
				if(!strcmp(buf, pnode->name))
				{
					strncpy(tempname, buf, NAMELEN-1);
					break;
				}
				pnode = pnode->next;
			}
			if(!pnode)
			{
				write(client_p->fd, "user name not exist\n", BUFLEN);
				sleep(1);
				continue;
			}

			write(client_p->fd, "\n\tinput you password:\n", BUFLEN);
			memset(buf, 0, BUFLEN);
			if((numbytes = recv(client_p->fd, buf, BUFLEN, 0)) == -1)
			{
				perror("recv in login");
				pthread_exit(NULL);
			}
			buf[--numbytes] = '\0';

#ifdef DEBUG_VERSION_
		printf("from:%s :%s\n", inet_ntoa(client_p->addr.sin_addr), buf);
		printf("node->name:%s\n", pnode->name);
		printf("client_p->user_name:%s///strlen:%d\n", client_p->user_name, 
				strlen(client_p->user_name));
#endif
			if(!strcmp(buf, pnode->pwd))
			{
				for(i=0; i<MAXPEOPLE; i++)
				{
					if((client[i].fd != -1) &&
							!strcmp(tempname,client[i].user_name))
					{
						break;
					}
				}

				//the user name already login
				if(i != MAXPEOPLE)
				{
					write(client_p->fd,"the user name have already login\n",
							BUFLEN);
					sleep(1);
					continue;
				}

				//if the user name not login then login
				else
				{
					strcpy(client_p->user_name, tempname); 
#ifdef DEBUG_VERSION
					printf("%s login success\n", client_p->user_name);
#endif
					return 1;
				}
			}
			else
			{
				write(client_p->fd, "password not match!!!\n", BUFLEN);			
				sleep(1);
			}
		}

		//going to regist
		else if(buf[0] == '2')
		{
			write(client_p->fd, "input you user name:\n", BUFLEN);
			memset(buf, 0, BUFLEN);
			if((numbytes = recv(client_p->fd, buf, BUFLEN, 0)) == -1)
			{
				perror("recv in regist");
				pthread_exit(NULL);
			}
			buf[--numbytes] = '\0';
			
			strcpy(tempname, buf);
			pnode = file_info;

			//check if the user the already exist
			while(pnode)
			{
				if(!strcmp(buf, pnode->name))
				{
					write(client_p->fd, "the user name already exist\n", BUFLEN);
					sleep(1);
					break;
				}
				pnode = pnode->next;
			}

			//if user name not exist
			if(!pnode)
			{
				write(client_p->fd, "input password:\n", BUFLEN);
				memset(buf, 0, BUFLEN);
				if((numbytes = recv(client_p->fd, buf, BUFLEN, 0)) == -1)
				{
					perror("recv in regist");
					pthread_exit(NULL);
				}
				buf[--numbytes] = '\0';
				strcpy(temppwd, buf);

				write(client_p->fd, "input you password again:\n", BUFLEN);
				memset(buf, 0, BUFLEN);
				if((numbytes = recv(client_p->fd, buf, BUFLEN, 0)) == -1)
				{
					perror("recv in regist");
					pthread_exit(NULL);
				}
				buf[--numbytes] = '\0';

				//passwork correct
				if(!strcmp(temppwd, buf))
				{
					pnode = malloc(sizeof(struct info));
					pnode->next = NULL;
					strcpy(pnode->name, tempname);
					strcpy(pnode->pwd, temppwd);

					pnode->next = file_info;
					file_info = pnode;
					save_info(pnode);
					write(client_p->fd, "regist success!!!\n", BUFLEN);
					sleep(1);
#ifdef DEBUG_VERSION
					printf("regist:%s:%s\n", pnode->name, pnode->pwd);
#endif
					continue;
				}
				else
				{
					write(client_p->fd, "password not match!!!\n", BUFLEN);
					sleep(1);
					continue;
				}
			}
		}
		
		else if(buf[0] == '3')
		{
			write(client_p->fd, "EXIT", BUFLEN);

			close(client_p);
			FD_ADDR_CLR(client_p);
			pthread_exit(NULL);
		}
	}
}

void save_info(struct info* pnode)
{
	FILE *fp;
	
	if((fp = fopen("client_info", "ab")) == NULL)
	{
		perror("fopen");
		exit(1);
	}
	
	fwrite(pnode, sizeof(struct info), 1, fp);
	fclose(fp);
}

void sendto_all(char* buf, fd_addr* client_p)
{
	int i = 0;
	char add_buf[BUFLEN] = {0};

	strcpy(add_buf, "[");
	strcat(add_buf, client_p->user_name);
	strcat(add_buf, "]:\n\t");
	strcat(add_buf, buf);
	strcat(add_buf, "\n______________\n");
	for(i=0; (i<MAXPEOPLE); i++)
	{
		if((client[i].fd != -1) && (client[i].fd != client_p->fd) && 
				(client[i].in_room_flag ==1))
		{
#ifdef DEBUG_VERSION
			printf("send to %s\n", inet_ntoa(client[i].addr.sin_addr));
#endif
			if(send(client[i].fd, add_buf, strlen(add_buf), 0) == -1)
			{
				perror("sendto error:");
				perror((char*)inet_ntoa(client[i].addr.sin_addr));
				continue;
			}
		}
	}
}

void chat_with_all(fd_addr* client_p)
{
	fd_set readfd;
	char buf[BUFLEN] = {0};
	int numbytes = 0;
	int i = 0;

	FD_ZERO(&readfd);
	while(1)
	{
		FD_SET(client_p->fd, &readfd);
		select((client_p->fd) + 1, &readfd, NULL, NULL, NULL);
		if(FD_ISSET(client_p->fd, &readfd))
		{
			memset(buf, 0, BUFLEN);
			if((numbytes = recv(client_p->fd, buf, BUFLEN, 0)) == -1)
			{
				perror("recv in sndto_all_user");
				//close(client_p->fd);
				return ;
			}
			buf[--numbytes] = '\0';

			if(!strcmp(buf, "quit") || !strcmp(buf, "Quit"))
			{
				sendto_all("<<<<<<<<<<<exit the room<<<<<<<<<<<", client_p);
				printf("%s Quit\n", inet_ntoa(client_p->addr.sin_addr));
				client_p->in_room_flag = 0;
				return;
			}
			//strcat(add_buf, buf);
			sendto_all(buf, client_p);			
		}

		FD_CLR(client_p->fd, &readfd);
	}
}

void chat_with_one(fd_addr* client_p)
{
	char* buf[BUFLEN] = {0};
	int numbytes;
	int i;
	
	for(i=0; i<MAXPEOPLE; i++)
	{
		
	}

}

int main()
{
	load_info();
	server();
	return 0;
}
