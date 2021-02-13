#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

volatile int int_count = 0;
volatile int tstp_count = 0;

void int_handler(int signal){
    int_count++;
}

void tstp_handler(int signal){
    tstp_count++;
}

int main(){

    struct sigaction sigact;
    sigset_t blk_set;

    sigaction(SIGINT, NULL, &sigact);
    sigact.sa_handler = &int_handler;
    sigaction(SIGINT, &sigact, NULL);

    sigaction(SIGTSTP, NULL, &sigact);
    sigact.sa_handler = &tstp_handler;
    sigaction(SIGTSTP, &sigact, NULL);
    
    sigemptyset(&blk_set);

    while (int_count + tstp_count < 10)
        sigsuspend(&blk_set);

    printf("Numero de SIGINT: %d\n", int_count);
    printf("Numero de SIGTSTP: %d\n", tstp_count);


    return 0;
}