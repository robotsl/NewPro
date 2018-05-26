#include "./server.h"
#include "/home/pi/Downloads/NewPro/src/MainControl.h"
#include "/home/pi/Downloads/NewPro/src/ControlTempSensor.h"
#include "/home/pi/Downloads/NewPro/src/ControlLEDS.h"
#include "/home/pi/Downloads/NewPro/src/ControlRadio.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 9000    //服务器端监听端口号
#define PORT1 9002    //服务器端监听端口号
#define MAX_BUFFER 200 //数据缓冲区最大值

int command(int head,int operator)
{
  int ret = 0;
  switch (head) {
  case 0:
      ret = local_command(operator==1?"off":"on",opt[0]);
      break;
  case 1:
      ret = local_command(operator==1?"off":"on",opt[1]);
      break;
  case 2:
      ret = local_command(operator==1?"off":"on",opt[2]);
      break;
  case 3:
        ret = local_command(operator==1?"off":"on",opt[4]);
        break;
  case 4:
        ret = local_command(operator==1?"off":"on",opt[5]);
        break;
  case 7:
        system("poweroff");
        break;
    return ret;
  }
}

int main() {
  pid_t pid = 0;
  struct sockaddr_in server_addr, client_addr;
  int server_sockfd, client_sockfd;
  int size, write_size;
  char buffer[MAX_BUFFER],str[MAX_BUFFER];
  int head, statues, operator,ret;
  DHT *dht = (DHT *)malloc(sizeof(DHT));

  if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) //创建Socket
  {
    perror("Socket Created Failed!\n");
    exit(1);
  }
  printf("Socket Create Success!\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);
  bzero(&(server_addr.sin_zero), 8);

  int opt = 1;
  int res = setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt,
                       sizeof(opt)); //设置地址复用
  if (res < 0) {
    perror("Server reuse address failed!\n");
    exit(1);
  }
  readData(dht);
  if (bind(server_sockfd, (struct sockaddr *)&server_addr,sizeof(server_addr)) == -1) //绑定本地地址
  {
    perror("Socket Bind Failed!\n");
    exit(1);
  }
  printf("Socket Bind Success!\n");

  if (listen(server_sockfd, 5) == -1) //监听
  {
    perror("Listened Failed!\n");
    exit(1);
  }
  printf("Listening ....\n");

  socklen_t len = sizeof(client_addr);

  printf("waiting connection...\n");
  if ((client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr,&len)) == -1) //等待客户端连接
  {
    perror("Accepted Failed!\n");
    exit(0);
    }
    printf("connection established!\n");
    printf("waiting message...\n");
    while (1) {
    memset(buffer, 0, sizeof(buffer)); //清空数据缓冲区

    if ((size = read(client_sockfd, buffer, MAX_BUFFER)) <= 0) //读取客户端的数据
    {
      perror("Recv Failed!\n");
      close(client_sockfd); //关闭Socket
      exit(1);
    }
    printf("size = %d\n",size);
    if (size != 0) {
      buffer[size] = '\0';
      printf("Recv msg from client*****: %s\n", buffer);
     }
      head = buffer[0] - 48;
      operator= buffer[1] - 48;
      statues = buffer[2] - 48;
      printf("in main head = %d,operator = %d,statues = %d\n",head,operator,statues);
      if (head == 4){
        	bzero(dht,sizeof(dht));
    		readData(dht);
   		sprintf(str,"%d%f",3,dht->TMP);
    		if ((ret = write(client_sockfd,str,sizeof(str))) < 0){
			printf("failed to send\n");
		}
		printf("send data size = %d\n",ret);
         	bzero(str,sizeof(str));
    		sprintf(str,"%d%f",4,dht->RH);
    		if ((ret = write(client_sockfd,str,sizeof(str))) < 0){
			printf("failed to send\n");
		}
		printf("send data size = %d\n",ret);
		continue;
      }else if (head == 8){
	 system("sudo poweroff");
	 return 0;
      }
      command(head, operator);
      //sprintf(buffer, "%c%c%c%c", head, operator, ret);
      //printf("in  main:buffer = %s\n",buffer);
      //write(client_sockfd, buffer, sizeof(buffer));
    }
  close(client_sockfd); //关闭Socket
  close(server_sockfd);

  return 0;
}
