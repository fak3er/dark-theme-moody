#include <winsock.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

struct sockaddr_in server ; //server public IPv4 adrress structure //
//server address create function 
void createadr( char address[16])
{server.sin_family=AF_INET;
server.sin_addr.s_addr=inet_addr(address);
server.sin_port=htons(80);
}


int main(int argc, char **argv){	
//Startup phase and declaring variables // 
WORD wVersionRequired=MAKEWORD(2,2); //socket implementation version 
WSADATA lpWSAData ; // specifications
SOCKET CLIENT_SOCKET; // socket descriptor
SOCKADDR_IN SERVER_ADDRESS ; 
SERVER_ADDRESS.sin_family=AF_INET;
SERVER_ADDRESS.sin_addr.s_addr=inet_addr("192.168.1.100");
SERVER_ADDRESS.sin_port=htons(80);
int bytes=0;
char request[100], response[100] ;
//*response=0;
int strp=WSAStartup(wVersionRequired,&lpWSAData);

if(!strp)
	printf("startup error %d\n", WSAGetLastError());
CLIENT_SOCKET=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

if(CLIENT_SOCKET<1)
	printf("socket create error %d\n", WSAGetLastError());

int cnt=connect(CLIENT_SOCKET, (SOCKADDR *)&SERVER_ADDRESS, sizeof(SOCKADDR_IN));
if(cnt<1)
printf("connect error %d\n", WSAGetLastError());

int loop=3;
while(loop--){

gets(request);

bytes=send(CLIENT_SOCKET, request, strlen(request)+1,0);

if(bytes<1)
printf("connect error %d\n", WSAGetLastError());
//printf("%d bytes sent\n", bytes)
	

bytes=recv(CLIENT_SOCKET,response, 100, 0 );
if(bytes<1)
printf("receive error %d\n", WSAGetLastError());
else
//printf("%d bytes received\n",bytes);
puts(response);	}
closesocket(CLIENT_SOCKET);
WSACleanup();
return 0;
}