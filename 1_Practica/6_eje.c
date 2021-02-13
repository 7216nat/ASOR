#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

int main() {
	printf("Longitud Máxima de Argumentos: %ld\n", sysconf(_SC_ARG_MAX));
	printf("Número máximo de hijos: %ld\n", sysconf(_SC_CHILD_MAX));
	printf("Número máximo de ficheros abiertos por el proceso: %ld\n", sysconf(_SC_OPEN_MAX));
	return 0;
}
