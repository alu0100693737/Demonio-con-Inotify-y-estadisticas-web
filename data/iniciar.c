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
}
