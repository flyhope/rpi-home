/*
 * carbon.c
 *
 *  Created on: 2017年4月23日
 *      Author: 李枨煊
 */


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>  /* netdb is necessary for struct hostent */

#define MAXDATASIZE 100

// 写入数据
short carbon_write(char host[], int port, char key[], int value, unsigned int time) {
	int sockfd, num;
	struct sockaddr_in server;

    if((sockfd=socket(AF_INET,SOCK_STREAM, 0))==-1) {
        return -1;
    }


    //解析域名，如果是IP则不用解析，如果出错，显示错误信息
    struct hostent *nlp_host;
    while ((nlp_host=gethostbyname(host))==0){
        printf("Resolve Error!\n");
    }

    bzero(&server,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr=((struct in_addr *)(nlp_host->h_addr))->s_addr;

	if(connect(sockfd, (struct sockaddr *)&server, sizeof(server))==-1) {
	   return -2;
	}

	char str[100];
	sprintf(str, "%s %d %d\n", key, value, time);
	printf("write:%s", str);

	// 发送数据
    if((num=send(sockfd,str,sizeof(str),0)) == -1) {
        return -3;
    }

    close(sockfd);
    return 1;
}
