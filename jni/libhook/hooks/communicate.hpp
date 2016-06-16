#ifndef COMMUNICATE_H__
#define COMMUNICATE_H__

#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>
#include "hook.h"

#define SREVER_IP "127.0.0.1"
#define SERVER_PORT 12345

typedef struct
{
	char application[100];
	char operation[10];
	char data[100];
}message_t;

class Communication {

private:
	
	static Communication* instance;

	int socket_fd;

	int init(){
		struct sockaddr_in remote_addr; //服务器端网络地址结构体

		memset(&remote_addr, 0, sizeof(remote_addr)); //数据初始化--清零
		remote_addr.sin_family = AF_INET; //设置为IP通信
		remote_addr.sin_addr.s_addr = inet_addr(SREVER_IP);//服务器IP地址
		remote_addr.sin_port = htons(SERVER_PORT); //服务器端口号

		/*创建客户端套接字--IPv4协议，面向连接通信，TCP协议*/
		if((socket_fd = socket(PF_INET, SOCK_STREAM, 0))<0)
		{
			perror("socket");
			return 1;
		}

		/*将套接字绑定到服务器的网络地址上*/
		if(connect(socket_fd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr))<0)
		{
			perror("connect");
			return 1;
		}

		printf("connected to server\n");
		return 0;
	}

	Communication(){
		init();
	}

public:
	static Communication* getInstance(){
		if(instance == NULL)
			instance = new Communication();
		return instance;
	}

	~Communication() {
        close(socket_fd);//关闭套接字
    }

    int sendData(string buf){
    	send(socket_fd, buf.c_str(), buf.length(), 0);
    	char msg[1024];
    	int length;
    	length = recv(socket_fd, msg, 1023, 0);
    	msg[length] = '\0';
    	if(strcmp(msg, "0") == 0){
    		HOOKLOG( "if allowed, no = %s", msg);
    		return 0;
    	}else{
    		HOOKLOG( "if allowed, yes = %s", msg);
    		return 1;
    	}
    }
};

Communication* Communication::instance = 0;

#endif