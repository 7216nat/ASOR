#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
    int file;

    file = open("fichero", O_CREAT, S_IREAD|S_IWRITE|S_IRGRP|S_IROTH|S_IXOTH);
    if (file < 0){
       perror("open() error.\n");
       exit(EXIT_FAILURE);
    }
    close(file);
    return 0;
}