#include"server.h"

inline void init_client(fd_addr client[])
{
	int i;
	for(i=0; i<MAXPEOPLE; i++)
	{
		client[i].fd = -1;
	}
}

void server()
{
	int sock_fd = -1;
	struct sockaddr_in my_addr;
	int addr_len = 0;
	int c_nums = 0; 
	int i;	
	fd_set readfds;
	pthread_t thread_id;

	init_client(client);
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(SERVPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 8);
	addr_len = sizeof(struct sockaddr_in);

	FD_ZERO(&readfds);

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
			exit(1);
		}

#ifdef DEBUG_VERSION
		printf("received a connection from %s\nfd:%d\nc_nums:%d\n", 
				inet_ntoa(client[c_nums].addr.sin_addr), 
				client[c_nums].fd, c_nums);
#endif
		/*
		if(!fork())
		{
			close(sock_fd);
			//send_menu(client[c_nums].fd);
			printf("in fork :::%d\n", client[c_nums].fd);
			msg_processor(&(client[c_nums]));
			FD_ADDR_CLR(client[c_nums]);
			close(client[c_nums].fd);
			exit(0);
		}*/
		pthread_create(&thread_id, NULL, &msg_processor, (void*)&client[c_nums]);

		c_nums++;
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
		write(client_p->fd, "\n\t*****************************\n", BUFLEN);
		write(client_p->fd,   "\t* (1) going to chatroom     *\n", BUFLEN);
		write(client_p->fd,   "\t* (2) going to private chat *\n", BUFLEN);
		write(client_p->fd,   "\t*****************************\n", BUFLEN);

		FD_SET(client_p->fd, &readfds);
		select((client_p->fd) + 1, &readfds, NULL, NULL, NULL);
		if(FD_ISSET(client_p->fd, &readfds))
		{
			if((numbytes = recv(client_p->fd, buf, BUFLEN, 0)) == 1)
			{
				perror("recv in send_all_user");
				close(client_p->fd);
				exit(1);
			}
			buf[numbytes] = '\0';
#ifdef DEBUG_VERSION
			printf("recv:%s\n",buf);
#endif
	
			if(buf[0] == '1')
			{
				sendto_all_user(client_p);
			}

			else if(buf[0] == '2')
			{
				//TODO SEND TO A USER
				//......
				//sendto_a_user(client_p, );
				printf("send to a user....\n");
			}
		}

		close(client_p->fd);
		FD_ADDR_CLR(client_p);
		FD_CLR(client_p->fd, &readfds);
	}
	return NULL ;
}

void sendto_all_user(fd_addr* client_p)
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
			if((numbytes = recv(client_p->fd, buf, BUFLEN, 0)) == -1)
			{
				perror("recv in sndto_all_user");
				close(client_p->fd);
				exit(1);
			}
			buf[numbytes] = '\0';
#ifdef DEBUG_VERSION
			printf("recv:%s||||| from:%s\n",buf, 
					inet_ntoa(client_p->addr.sin_addr));

			printf("in %d:\n",client_p->fd);
			for(i=0; i<MAXPEOPLE; i++)
			{
				printf("%d\t", client[i].fd);
			}
			printf("\n");
#endif
			if(!strcmp(buf, "quit\n") || !strcmp(buf, "Quit\n"))
			{
				
				printf("%s Quit\n", inet_ntoa(client_p->addr.sin_addr));
				return;
			}
			for(i=0; (i<MAXPEOPLE)&&(client[i].fd != (client_p->fd)); i++)
			{
				if(client[i].fd != -1)
				{
					write(client[i].fd,inet_ntoa(client_p->addr.sin_addr),BUFLEN);
#ifdef DEBUG_VERSION
					printf("send to %s\n", inet_ntoa(client[i].addr.sin_addr));
#endif
					if(send(client[i].fd, buf, strlen(buf), 0) == -1)
					{
						perror("sendto error:");
						perror((char*)inet_ntoa(client[i].addr.sin_addr));
						continue;
					}
				}
			}

		}

		FD_CLR(client_p->fd, &readfd);
	}
}

void sendto_a_user(fd_addr* from, fd_addr* to)
{

}

int main()
{
	server();
	return 0;
}
