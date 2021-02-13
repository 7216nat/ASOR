#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUF_SIZE 256
int main (void){
   fd_set rfds;
   int pipe1, pipe2;
   char *fifo1 = "fifo1";
   char *fifo2 = "fifo2";
   char buf[BUF_SIZE+1];
 
   if (mkfifo(fifo1, 0666) < 0){
       perror("mkfifo() error");
       exit(EXIT_FAILURE);
   }
   if (mkfifo(fifo2, 0666) < 0){
       perror("mkfifo() error");
       exit(EXIT_FAILURE);
   }
 
   pipe1 = open(fifo1, O_RDONLY | O_NONBLOCK);
   if (pipe1 < 0){
       perror("open() error");
       exit(EXIT_FAILURE);
   }
   pipe2 = open(fifo2, O_RDONLY | O_NONBLOCK);
   if (pipe2 < 0){
       close(pipe1);
       perror("open() error");
       exit(EXIT_FAILURE);
   }
 
   int nfds = (pipe1 < pipe2) ? pipe2 + 1: pipe1 + 1;
   int bytes;
 
   while (1){
       FD_ZERO(&rfds);
       FD_SET(pipe1, &rfds);
       FD_SET(pipe2, &rfds);
       if (select(nfds, &rfds, NULL, NULL, NULL) < 0){
           close(pipe1);
           close(pipe2);
           perror("select() error");
           exit(EXIT_FAILURE);
       }
 
       if (FD_ISSET(pipe1, &rfds)){
           while ((bytes =read(pipe1, buf, BUF_SIZE)) > 0){
               buf[bytes] = '\0';
               printf("Mensaje desde %s: %s\n", fifo1, buf);
           }
           close(pipe1);
           pipe1 = open(fifo1, O_RDONLY | O_NONBLOCK);
       }
       else if (FD_ISSET(pipe2, &rfds)){
           while ((bytes =read(pipe2, buf, BUF_SIZE)) > 0){
               buf[bytes] = '\0';
               printf("Mensaje desde %s: %s\n", fifo2, buf);
           }
           close(pipe2);
           pipe2 = open(fifo2, O_RDONLY | O_NONBLOCK);
       }
   }
   return 0;
 
}
