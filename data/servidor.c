#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
	int sockfd, newsockfd, portnumber;
	int pid;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int i;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) 
		printf("Error\n");
	
	bzero((char*)&serv_addr, sizeof(serv_addr));//No hace falta, limpiando servidor

	portnumber = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;//protocolo de internet
	serv_addr.sin_addr.s_addr = INADDR_ANY; //ip del ordenador
	serv_addr.sin_port = htons(portnumber); //transformacion para que el ordenador entienda el numero de puerto
	
	if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
		printf("Error\n");
	listen(sockfd, 5);

	
	clilen = sizeof(cli_addr);

	while(1) { //enviar mas de un mensaje
		newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);

		if(newsockfd < 0)
			printf("Error, socket no activado");
		pid = fork();
		if(pid < 0) 
			printf("Error asignando pid");
		if(pid == 0) {
			close(sockfd);

			//Limpieza del buffer
			bzero(buffer, 256);
			i = read(newsockfd, buffer, 255);
			if(i<0)
				printf("Error");
	
			printf("Mensaje recibido: %s\n", buffer);
			exit(0);
		} else  {
			
			close(newsockfd);
		}
	}
	close(sockfd);
	return 0;
}
