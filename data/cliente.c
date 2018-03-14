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
	
	char *buffer = NULL;
	int string_size, read_size;
	
	FILE* fFile = fopen(argv[3], "r");
	
/*	const int MAX_SIZE = 99999;
	char buf[MAX_SIZE];
	
	
	
*/	
	 // Seek the last byte of the file
       fseek(fFile, 0, SEEK_END);
       // Offset from the first to the last byte, or in other words, filesize
       string_size = ftell(fFile);
       // go back to the start of the file
       rewind(fFile);

       // Allocate a string that can hold it all
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, fFile);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       buffer[string_size] = '\0';

       if (string_size != read_size) {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;
       }


	/*if (!fgets(buffer, 256, fFile)) {
		printf("Read error\n");
		exit(1);
	}*/
	printf("EA %s \n", buffer);
	
	portnumber = atoi(argv[2]);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) 
		printf("Error 1");
	
	server = gethostbyname(argv[1]);
	if(server == NULL)
		printf("Error 2\n");

	printf("YES %s", argv[3]);
	bzero((char*)&serv_addr, sizeof(serv_addr));//No hace falta, limpiando servidor

	serv_addr.sin_family = AF_INET;//protocolo de internet
	bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);

	
	serv_addr.sin_port = htons(portnumber); //transformacion para que el ordenador entienda el numero de puerto
	
	if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
		printf("No se pudo conectar Error 3\n");

	printf("Introducir el mensaje:\n");
//	bzero(buffer, 256);
//	fgets(buffer, 255, stdin);
	i = write(sockfd, buffer, strlen(buffer));
	if(i < 0) //no se pudo escribir en el socket
		printf("Error 4");
	close(sockfd);
	return 0;
}
