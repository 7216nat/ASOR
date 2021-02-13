#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

volatile bool stop = false;

void handler(int signal){
  stop = true;
}

int main(int argc, char **argv) {

    struct sigaction sigact;
    int segundos;

    if (argc != 2) {
        printf("usage: %s <integer>.\n", argv[0]);
		exit(EXIT_FAILURE);
    }
    
    printf("[%d] pid Proceso.\n", getpid());
    sigaction(SIGUSR1, NULL, &sigact);
    sigact.sa_handler = &handler;
    sigaction(SIGUSR1, &sigact, NULL); 

    segundos = atoi(argv[1]);

    int i = 0;
    while (i < segundos && !stop) {
        i++;
        sleep(1);
    }

    if (!stop) {
        printf("Se ha borrado el ejecutable\n");
        remove(argv[0]);
    } else 
        printf("Se ha recibido la señal SIGUSR1\n");

    return 0;
}