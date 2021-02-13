#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUF_SIZE 64

int main(int argc, char *argv[]){
    int pipeph[2], pipehp[2];
    pid_t cpid;
    int bytes;
    char buf[BUF_SIZE +1];
    char mensaje;
    if (argc != 1){
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipeph) == -1 || pipe(pipehp) == -1){
        perror("pipe() error\n");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1){
        perror("fork() error\n");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0){ // proceso hijo
        close(pipeph[1]); 
        close(pipehp[0]);
        int i = 0;
        while((bytes = read(pipeph[0], buf, BUF_SIZE)) > 0){
            buf[bytes] = '\0';
            printf("Hijo: mensaje recibido: %s", buf);
            i++;
            if (i < 10){
                mensaje = 'l';
                write(pipehp[1], &mensaje, 1);
            }
            else {
                mensaje= 'q';
                write(pipehp[1], &mensaje, 1);
                break;
            }
        }

        close(pipeph[0]);
        close(pipehp[1]);
        printf("Hijo: 10 mensajes recibidos, FIN\n");
        _exit(EXIT_SUCCESS);
    }
    else {
        close(pipeph[0]);
        close(pipehp[1]);
        while((bytes = read(0, buf, BUF_SIZE)) > 0){
            buf[bytes] = '\0';
            write(pipeph[1], buf, BUF_SIZE);
            read(pipehp[0], &mensaje, 1);
            if (mensaje == 'q') break;
        }
        close(pipeph[1]);
        close(pipehp[0]);
        wait(NULL);
        printf("Padre: 10 mensajes enviados, FIN\n");
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_FAILURE);
}
