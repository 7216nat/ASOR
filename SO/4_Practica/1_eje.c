#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    int pipefd[2];
    pid_t cpid;

    if (argc != 5){
        fprintf(stderr, "Usage: %s <comando> <argumento> <comando> <argumento>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1){
        perror("pipe() error\n");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1){
        perror("fork() error\n");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0){ // proceso hijo
        dup2(pipefd[0], 0); // redirigir la entrada estandar a la salida de pipe
        close(pipefd[0]);   // cerrar todos los descriptores
        close(pipefd[1]);
        execlp(argv[3], argv[3], argv[4], (char *)NULL);
    }
    else {
        dup2(pipefd[1], 1); // redirigir la salida estandar a la entrada de pipe
        close(pipefd[0]);
        close(pipefd[1]);
        execlp(argv[1], argv[1], argv[2], (char *)NULL);
    }

    exit(EXIT_FAILURE);
}
