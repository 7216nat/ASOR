#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int main(int argc, char **argv) {

    int ret = 0;
    struct stat _stat;
    char sym[PATH_MAX];
    char hard[PATH_MAX];

	if (argc < 2) {
		 printf("usage: %s <ruta>.\n", argv[0]);
		 exit(EXIT_FAILURE);
	}

	ret = stat(argv[1], &_stat);
	if (ret < 0) {
		perror("stat() error.\n");
		exit(EXIT_FAILURE);
	}

    mode_t mode = _stat.st_mode;
    if (!S_ISREG(mode)) {
		printf("%s no es un fichero regular.\n", argv[1]);
        exit(EXIT_FAILURE);
    }
	
    strcpy(sym, argv[1]);
    strcpy(hard, argv[1]);
    strcat(sym, ".sym");
    strcat(hard, ".hard");

    if (link(argv[1],hard) < 0) {
		perror("link() error.\n");
	    exit(EXIT_FAILURE);
    } 

	if (symlink(argv[1],sym) == -1) {
		perror("symlink() error.\n");
	    exit(EXIT_FAILURE);
	} 
	return ret;
}