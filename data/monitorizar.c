//indent -kr -nut -i3 mySource.cpp
#include <sys/inotify.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


#define BUF_LEN (10*(sizeof(struct inotify_event) + NAME_MAX + 1))
#define FICHERO_ESTADISTICAS "estadisticas.txt"

static void mostrar(struct inotify_event *e, char *argumentos[], int iteracion) {
   
   FILE *f = fopen(FICHERO_ESTADISTICAS, "a");
   if (f == NULL) {
       printf("Error opening file!\n");
       exit(1);
   }
   
   //fprintf(f, "wd=%2d; ", e->wd);
   fprintf(f, "%d. Carpeta: %s ", iteracion, argumentos[(e->wd - 1)]);
      
   if (e->cookie > 0)  {
      fprintf(f, "cookie = %4d; ", e->cookie);
      //printf("cookie = %4d; ", e->cookie);
   }

   if (e->mask & IN_CREATE) 
      fprintf(f, "mask=IN_CREATE");
      //printf("mask=IN_CREATE");
   
   if (e->mask & IN_MODIFY) 
      fprintf(f, "mask= IN_MODIFY");
   
   if (e->mask & IN_ACCESS)  //file was accessed
      fprintf(f, "mask=IN_ACCESS");
      
   if (e->mask & IN_ATTRIB)     //file metadata change  
      fprintf(f, "mask=IN_ATTRIB");
      
   if (e->mask & IN_CLOSE_WRITE)
      fprintf(f, "mask=IN_CLOSE_WRITE");
      
   if (e->mask & IN_CLOSE_NOWRITE)
      fprintf(f, "mask=IN_CLOSE_NOWRITE");
      
   if (e->mask & IN_DELETE)
      fprintf(f, "mask=IN_DELETE");
      
   if (e->mask & IN_DELETE_SELF)
      fprintf(f, "mask=IN_DELETE_SELF");
      
   if (e->mask & IN_MOVE_SELF)
      fprintf(f, "mask=IN_MOVE_SELF");
      
   if (e->mask & IN_MOVED_FROM)
      fprintf(f, "mask=IN_MOVED_FROM");
      
   if (e->mask & IN_MOVED_TO)
      fprintf(f, "mask=IN_MOVED_TO");
      
   if (e->mask & IN_OPEN)
      fprintf(f, "mask=IN_OPEN");

   if (e->len > 0)
      fprintf(f, " nombre= %s", e->name);
   
   fprintf(f, "\n");

   if(f != NULL) 
      fclose(f);
}

int main(int argc, char *argv[]) {
  time_t rawtime;
  const struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  
  printf ( "Current local time and date: %s", asctime (timeinfo) );
   int minutoActual = timeinfo->tm_min;

   //escribir el nombre de la carpeta
   char* argumentos[argc -1]; 
   int i;
   printf("Las carpetas son: \n\t");
   for(i = 1; i < argc; i++) {
      argumentos[i - 1] = argv[i];
      printf("\n \t*  %s \n", argumentos[i - 1]);
   }
   //Num lineas fichero
   int iteracion = 0;
    while (1) {
      int inotifyFd, wd, i;
      char buf[BUF_LEN];
      ssize_t numRead;
      char *buffer;
      struct inotify_event *event;
      inotifyFd = inotify_init();
      if (inotifyFd == -1) {
         printf("Error 1\n");
         exit(1);
      }
   
      for (i = 1; i < argc; i++) {
         printf("Monitorizando: %s\n", argv[i]);
         wd = inotify_add_watch(inotifyFd, argv[i], IN_ALL_EVENTS);
         if (wd == -1) {
            printf("Error 2\n");
            exit(1);
         }
      }
   
      for (;;) {
         numRead = read(inotifyFd, buf, BUF_LEN);
         for (buffer = buf; buffer < buf + numRead;) {
            event = (struct inotify_event *) buffer;
            iteracion++;
            mostrar(event, argumentos, iteracion);
            buffer += sizeof(struct inotify_event) + event->len;
         }

         time ( &rawtime );
         timeinfo = localtime ( &rawtime );
         //printf ( "Current2 local time and date: %s", asctime (timeinfo) );
         printf("minuto anterior: %d, actual %d:%d \n", minutoActual, timeinfo->tm_min, timeinfo->tm_sec);
         if(minutoActual != timeinfo->tm_min) {
            printf("A pasado un min, subir información");
            int status = system("./data/cliente localhost 8888 estadisticas.txt");

            minutoActual = timeinfo->tm_min;
            printf("minuto actual ahora vale %d", minutoActual);
            remove(FICHERO_ESTADISTICAS);
            iteracion = 0;
         }
      }

   }
//exit(0);
}
