#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    
    sigset_t blk_set, pend;
    char *env; 
    int segundos;

    sigemptyset(&blk_set);
    sigemptyset(&pend);
    sigaddset(&blk_set, SIGINT);
    sigaddset(&blk_set, SIGTSTP);

    sigprocmask(SIG_BLOCK, &blk_set, NULL);

    env = getenv("SLEEP_SECS");
    if (env == NULL){
        setenv("SLEEP_SECS", "10", 1);
        env = getenv("SLEEP_SECS");
    }
    segundos = atoi(env);
    printf("[%d] Se va a dormir el proceso durante %d segundos\n", getpid(), segundos);
    sleep(segundos);

    sigpending(&pend);

    if (sigismember(&pend, SIGINT)) {
        printf("Se ha recibido la señal SIGINT\n");
        sigdelset(&blk_set, SIGINT);
    } 
    if (sigismember(&pend, SIGTSTP)) {
        printf("Se ha recibido la señal SIGTSTP, fg para desbloquear\n");
    }

    sigprocmask(SIG_UNBLOCK, &blk_set, NULL);
    printf("Prueba de que ha recibido TSTP\n");

    return 0;
}