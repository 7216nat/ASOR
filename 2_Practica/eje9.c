#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>
#include <locale.h>

int main(int argc, char **argv) {

    int ret = 0;
    struct stat buff;

	if (argc < 2) {
		 printf("usage: %s <ruta>.\n", argv[0]);
		 exit(EXIT_FAILURE);
	}

	ret = stat(argv[1], &buff);
	if (ret < 0) {
		perror("stat() error.\n");
		exit(EXIT_FAILURE);
	}

	printf("MAJOR: %d\n", major(buff.st_dev));
	printf("MINOR: %d\n", minor(buff.st_dev));
	printf("I-Node: %ld\n", buff.st_ino);
	printf("MODE: %d -> ",buff.st_mode);

	mode_t mode = buff.st_mode;

	if (S_ISLNK(mode)){
		printf("es un enlace simbólico.\n");
	} else if (S_ISREG(mode)) {
		printf("es un fichero ordinario.\n");
	} else if (S_ISDIR(mode)) {
		printf("es un directorio.\n");
	}

    char buf[100];
	setlocale(LC_ALL, "es_ES.utf8");
	
	time_t t = buff.st_atime;
	struct tm *tm= localtime(&t);
    strftime(buf, 100, "%A, %d de %B de %Y, %H:%M", tm);
	printf("Último acceso (Acceso): %s\n", buf);

	t = buff.st_mtime;
	tm= localtime(&t);
    strftime(buf, 100, "%A, %d de %B de %Y, %H:%M", tm);
	printf("Último acceso (Modificacion): %s\n", buf);

	t = buff.st_ctime;
	tm= localtime(&t);
    strftime(buf, 100, "%A, %d de %B de %Y, %H:%M", tm);
	printf("Último acceso (C, inode modificacion): %s\n", buf);

	return ret;
}