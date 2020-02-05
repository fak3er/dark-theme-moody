#include <stdio.h>
#include <string.h>
#include <winsock.h>
int main(int argc, char **argv)
{  WORD wVersionRequired=MAKEWORD(2,2);
	WSADATA lpWSAData ; 
	SOCKET SERVER_SOCKET, CLIENT_SOCKET;
	SOCKADDR_IN server_address, client_address ; 
	char request[100]="", response[100];
	int serveraddrsize=sizeof(SOCKADDR_IN),clientaddrsize=sizeof(SOCKADDR_IN);
	printf("%d\n",WSAStartup(wVersionRequired,&lpWSAData));
	SERVER_SOCKET=socket(AF_INET,SOCK_STREAM,0);
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(80) ;
	server_address.sin_addr.s_addr=inet_addr("192.168.1.100");
	printf("%d\n", SERVER_SOCKET);
	if(bind(SERVER_SOCKET, (struct sockaddr *)&server_address, serveraddrsize)!=0)
		printf("bind error %d\n", WSAGetLastError());
	if(listen(SERVER_SOCKET,SOMAXCONN)!=0) 
		printf("listen failed\n");
	else 
		printf("server listening on port :80\n");
	CLIENT_SOCKET=accept(SERVER_SOCKET,(struct sockaddr *)&client_address, &clientaddrsize );
    printf("accept error %d code \n",WSAGetLastError());
 	int bytes,loop=3;
 	  while(loop--){bytes=recv(CLIENT_SOCKET,request,100,0);
 	if(bytes==0)
 		printf("connection closed :(\n");
 	else if(bytes==-1) 
 		printf("socket error code %d\n",WSAGetLastError());
 	else {	
 		//printf("%d bytes\n", bytes);
 		puts(request);
 	      }
 	      gets(response) ;
 	  bytes= send(CLIENT_SOCKET,response,strlen(response)+1,0);
 	  if(bytes<1)
 	  printf("send failed %d\n", WSAGetLastError());
 	  else
 	  //printf("%d bytes sent\n", bytes)
 	  	;	
 	}
 	closesocket(SERVER_SOCKET);
 	closesocket(CLIENT_SOCKET);
	WSACleanup();
}