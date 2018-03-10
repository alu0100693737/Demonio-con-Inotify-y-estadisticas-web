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

#define BUF_LEN (10*(sizeof(struct inotify_event) + NAME_MAX + 1))

static void mostrar(struct inotify_event *e) {
   
   FILE *f = fopen("file.txt", "a");
      if (f == NULL) {
          printf("Error opening file!\n");
          exit(1);
      }
   
   fprintf(f, "wd=%2d; ", e->wd);
   
   if (e->cookie > 0)  {
      fprintf(f, "cookie = %4d; ", e->cookie);
      //printf("cookie = %4d; ", e->cookie);
   }

   if (e->mask & IN_CREATE) 
      fprintf(f, "mask=IN_CREATE\n");
      //printf("mask=IN_CREATE");
   
   if (e->mask & IN_MODIFY) 
      fprintf(f, "mask= IN_MODIFY\n");
   
   if (e->mask & IN_ACCESS)  //file was accessed
      fprintf(f, "mask=IN_ACCESS\n");
      
   if (e->mask & IN_ATTRIB)     //file metadata change  
      fprintf(f, "mask=IN_ATTRIB\n");
      
   if (e->mask & IN_CLOSE_WRITE)
      fprintf(f, "mask=IN_CLOSE_WRITE\n");
      
   if (e->mask & IN_CLOSE_NOWRITE)
      fprintf(f, "mask=IN_CLOSE_NOWRITE\n");
      
   if (e->mask & IN_DELETE)
      fprintf(f, "mask=IN_DELETE\n");
      
   if (e->mask & IN_DELETE_SELF)
      fprintf(f, "mask=IN_DELETE_SELF\n");
      
   if (e->mask & IN_MOVE_SELF)
      fprintf(f, "mask=IN_MOVE_SELF\n");
      
   if (e->mask & IN_MOVED_FROM)
      fprintf(f, "mask=IN_MOVED_FROM\n");
      
   if (e->mask & IN_MOVED_TO)
      fprintf(f, "mask=IN_MOVED_TO\n");
      
   if (e->mask & IN_OPEN)
      fprintf(f, "mask=IN_OPEN\n");

   if (e->len > 0)
      fprintf(f, "nombre= %s\n", e->name);
   
   if(f != NULL) 
      fclose(f);
}

int main(int argc, char *argv[]) {
   
   char* carpetas = argv[];
   printf("las carpetas son %d", argc);
   printf("Entrando en monitorizar\n");
   
   while (1) {
      int inotifyFd, wd, i;
      char buf[BUF_LEN];
      ssize_t numRead;
      char *buffer;
      struct inotify_event *event;
      inotifyFd = inotify_init();
      if (inotifyFd == -1) {
         printf("Error 1");
         exit(1);
      }

      for (i = 1; i < argc; i++) {
         printf("Monitorizando: %s", argv[i]);
         wd = inotify_add_watch(inotifyFd, argv[i], IN_ALL_EVENTS);
         if (wd == -1) {
            printf("Error 2");
            exit(1);
         }
      }

      for (;;) {
         numRead = read(inotifyFd, buf, BUF_LEN);
         for (buffer = buf; buffer < buf + numRead;) {
            event = (struct inotify_event *) buffer;
            mostrar(event);
            buffer += sizeof(struct inotify_event) + event->len;
         }
      }
   }
//exit(0);
}
