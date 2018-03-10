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
   printf("wd=%2d; ", e->wd);
   if (e->cookie > 0)
      printf("cookie = %4d; ", e->cookie);

   if (e->mask & IN_CREATE)
      printf("mask=IN_CREATE");
   if (e->mask & IN_MODIFY)
      printf("mask= IN_MODIFY");
   if (e->mask & IN_ACCESS)     //file was accessed
      printf("mask=IN_ACCESS");
   if (e->mask & IN_ATTRIB)     //file metadata change  
      printf("mask=IN_ATTRIB");
   if (e->mask & IN_CLOSE_WRITE)
      printf("mask=IN_CLOSE_WRITE");
   if (e->mask & IN_CLOSE_NOWRITE)
      printf("mask=IN_CLOSE_NOWRITE");
   if (e->mask & IN_DELETE)
      printf("mask=IN_DELETE");
   if (e->mask & IN_DELETE_SELF)
      printf("mask=IN_DELETE_SELF");
   if (e->mask & IN_MOVE_SELF)
      printf("mask=IN_MOVE_SELF");
   if (e->mask & IN_MOVED_FROM)
      printf("mask=IN_MOVED_FROM");
   if (e->mask & IN_MOVED_TO)
      printf("mask=IN_MOVED_TO");
   if (e->mask & IN_OPEN)
      printf("mask=IN_OPEN");

   if (e->len > 0)
      printf("nombre= %s\n", e->name);
   else
      printf("\n");
}

int main(int argc, char *argv[]) {
   printf("Entrando en monitorizar");
   
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
