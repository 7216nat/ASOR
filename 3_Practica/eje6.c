#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <limits.h>
int main() {

    pid_t pid, sid;
    char cwd[PATH_MAX];
    struct rlimit limit;

    pid = fork();
        
    if (pid == 0){
        sid = setsid();
        if (sid < 0){
            perror("setsid() error.\n");
            exit(EXIT_FAILURE);
        }
        if (chdir("/tmp")< 0){
            perror("chdir() error.\n");
            exit(EXIT_FAILURE);
        }

        //sleep(5);
        printf("[%d] Proceso hijo.\n",getpid());
        
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        printf("GID: %d\n", getgid());
        printf("SID: %d\n", getsid(getpid()));

        if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
            perror("getrlimit() error.\n");
            exit(EXIT_FAILURE);
        }
        printf("LIMITE: %ld\n", limit.rlim_max);
        
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("DIRECTORIO ACTUAL: %s\n", cwd);
        } else {
            perror("getcwd() error");
            exit(EXIT_FAILURE);
        }
        printf("[%d] El proceso hijo terminó de ejecutarse.\n", getpid());
        }
    else if (pid > 0) {
        sleep(100);
        printf("[%d] El proceso padre terminó de ejecutarse.\n", getpid());
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}