#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char *argv[]){

    char *fifo = "fifo";
    int fd;
    if (argc != 1){
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (mkfifo(fifo, 0666) < 0){
        perror("mkfifo() error");
        exit(EXIT_FAILURE);
    }

    fd = open(fifo, O_WRONLY);
    if (fd < 0){
        perror("open() error");
        exit(EXIT_FAILURE);
    }

    dprintf(fd, "%s\n", argv[0]);
    close(fd);
    return 0;
}