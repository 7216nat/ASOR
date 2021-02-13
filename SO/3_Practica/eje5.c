#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <limits.h>

int main() {

    char cwd[PATH_MAX];
    struct rlimit limit;

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
    return 0;
}