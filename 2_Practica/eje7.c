#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
    int file;
    umask(0027);
    file = open("fichero", O_CREAT, 0666);
    if (file < 0){
       perror("open() error.\n");
       exit(EXIT_FAILURE);
    }
    close(file);
    return 0;
}