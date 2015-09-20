#include"server.h"

inline void init_client(fd_addr client[])
{
	int i;
	for(i=0; i<MAXPEOPLE; i++)
	{
		client[i].fd = -1;
		memset(client[i].user_name, 0, 10);
		client[i].in_room_flag = 0;
	}
}

void server()
{
	int sock_fd = -1;
	struct sockaddr_in my_addr;
	int addr_len = 0;
	int c_nums = 0; 
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
			buf[numbytes] = '\0';
#ifdef DEBUG_VERSION
			printf("recv:%s\n",buf);
#endif
	
			if(buf[0] == '1')
			{
				printf("%s add to room\n", inet_ntoa(client_p->addr.sin_addr));
				client_p->in_room_flag = 1;
				//sendto_all_user(client_p);
				chat_with_all(client_p);
			}

			else if(buf[0] == '2')
			{
				//TODO SEND TO A USER
				//......
				//chat_with_one(client_p, );
				printf("send to a user....\n");
			}
			else if(buf[0] == '3')
			{
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

int client_login(fd_addr* client_p)
{

}

int client_register(fd_addr* client_p)
{
}

void sendto_all(char* buf, fd_addr* client_p)
{
	int i = 0;
	char add_buf[BUFLEN] = {0};

	strcpy(add_buf, "[");
	strcat(add_buf, (char*)inet_ntoa(client_p->addr.sin_addr));
	strcat(add_buf, "]:\n");
	strcat(add_buf, buf);
	strcat(add_buf, "______________\n");
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
			buf[numbytes] = '\0';

			if(!strcmp(buf, "quit\n") || !strcmp(buf, "Quit\n"))
			{
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

void chat_with_one(fd_addr* from, fd_addr* to)
{

}

int main()
{
	server();
	return 0;
}
