#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> //host

int main(int argc, char *argv[]) {
	int sockfd, portnumber, i;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];
	
	portnumber = atoi(argv[2]);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) 
		printf("Error 1");
	
	server = gethostbyname(argv[1]);
	if(server == NULL)
		printf("Error 2");

	bzero((char*)&serv_addr, sizeof(serv_addr));//No hace falta, limpiando servidor

	serv_addr.sin_family = AF_INET;//protocolo de internet
	bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);

	
	serv_addr.sin_port = htons(portnumber); //transformacion para que el ordenador entienda el numero de puerto
	
	if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
		printf("Error 3");

	printf("Introducir el mensaje:");
	bzero(buffer, 256);
	fgets(buffer, 255, stdin);
	i = write(sockfd, buffer, strlen(buffer));
	if(i < 0) //no se pudo escribir en el socket
		printf("Error 4");
	close(sockfd);
	return 0;
}
