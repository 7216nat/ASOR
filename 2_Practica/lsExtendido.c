#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {

	if (argc < 2) {
		 printf("usage: %s <ruta>.\n", argv[0]);
		 exit(EXIT_FAILURE);
	}
    
    DIR *dir = opendir(argv[1]);
    if (dir == NULL ) {
        printf("opendir() error.\n");
        exit(EXIT_FAILURE);
    }

    struct dirent *curr;
    struct stat _stat;
    size_t sizeArg = strlen(argv[1]), _size;
    curr = readdir(dir);
    unsigned int totalsize = 0;
    char *path;

    while (curr != NULL) {
        _size = sizeArg + strlen(curr->d_name)+ 2;
        path = malloc(sizeof(char)*_size);
        sprintf(path, "%s/%s", argv[1], curr->d_name);
        path[_size] = '\0';

        if (stat(path, &_stat) < 0) {
            printf("stat() error.\n");
            free(path);
            closedir(dir);
            exit(EXIT_FAILURE);
        }
        else {
            if (S_ISREG(_stat.st_mode)) {
                if ((S_IEXEC | S_IXGRP | S_IXOTH) &_stat.st_mode)
                    printf("%s* \n", curr->d_name);
                else 
                    printf("%s \n", curr->d_name);
                 totalsize = totalsize + _stat.st_size;
            } 
            else if (S_ISDIR(_stat.st_mode)) {
                printf("%s/ \n", curr->d_name);
            }
            else if (S_ISLNK(_stat.st_mode)) {
                char *linkpath = malloc(_stat.st_size + 1);
                readlink(path, linkpath, _stat.st_size);
                linkpath[_stat.st_size] = '\0';
                printf("%s->%s \n", curr->d_name, linkpath);
                free(linkpath);
            }
        }
        free(path);
        curr = readdir(dir);
    }
    printf("totalBytes: %.1f kB. \n", (float) totalsize/1024.0);
    closedir(dir);
    return 0;   
}