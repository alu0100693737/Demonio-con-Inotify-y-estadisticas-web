#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main(void) {
//Tenemos que crear el demonio
   pid_t pid, sid;              //identificador del proceso y de la sesion

  /* FILE *aux = popen("pgrep -c iniciar", "r");
   //system("pgrep -c iniciar");

   char buff[255];
   fscanf(aux, "%s", buff);
   //printf("Demonio num: %s\n", buff );
   int valor = buff[0];
   valor -= 48;                 //Conversion explicita a int
   //printf("Primer valor %d", valor);

   fclose(aux);

   if (valor > 1) {
      printf
          ("\nYa ha sido creado anteriormente.\nNO PUEDE INICIARSE UN SEGUNDO DEMONIO, puede parar, monitorear una carpeta o cambiar el tiempo de sincronizacion\n");
      exit(1);
   } else {*/
      //printf("\nCreando el pid");
      pid = fork();             //Creamos el demonio
      printf("\nPID vale %d", pid);

      if (pid < 0) {
         exit(1);
      }

      if (pid > 0) {

         exit(0);
      }
      //cambiamos la mascara
      umask(0);
      sid = setsid();

      if (sid < 0) {
         exit(1);
      }
      //cambiar al directorio raiz
      if (chdir("/") < 0) {
         printf("Error 3");
         exit(1);
      }

      close(STDIN_FILENO);
      close(STDOUT_FILENO);
      close(STDERR_FILENO);

      while (1) {
         //demonio
      }

      exit(0);
 //  }
}
