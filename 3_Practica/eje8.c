#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv){

    pid_t pid, sid;
    int fdout, fderr, fdnull;
    if (argc < 2) {
		printf("usage: %s <command>.\n", argv[0]);
		exit(EXIT_FAILURE);
	}
    
    pid = fork();

    if (pid == 0){
        umask(0);
        sid = setsid();
        if (sid < 0){
            perror("setsid() error.\n");
            exit(EXIT_FAILURE);
        }
        printf("[%d] Proceso hijo.\n",getpid());
        printf("ejecute <ps aux | grep %d> para ver que esta ejecutando.\n", getpid());
        printf("ejecute <sudo cat /tmp/daemon.out> al cabo de 10 segundos para ver el resultado\n");
        fdout = open("/tmp/daemon.out",O_CREAT | O_WRONLY | O_TRUNC, 0666);
        fderr = open("/tmp/daemon.err", O_CREAT | O_WRONLY| O_TRUNC, 0666);
        fdnull = open("/dev/null", O_CREAT | O_WRONLY, 0666);
        dup2(fderr,2);
        dup2(fdout, 1);
        dup2(fdnull, 0);
        sleep(10);
        
        if (execvp(argv[1], argv + 1) < 0) {
            perror("execvp() error.\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0) {
        printf("[%d] El proceso padre terminó de ejecutarse.\n", getpid());
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}