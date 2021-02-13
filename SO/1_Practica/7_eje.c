#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

int main() {
   char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
   	printf("Current working dir: %s\n", cwd);
	printf("Número máximo de enlaces,: %ld\n", pathconf(cwd, _PC_LINK_MAX));
	printf("Tamaño máximo de una ruta: %ld\n", pathconf(cwd, _PC_PATH_MAX));
	printf("Tamaño máximo de un nombre de fichero: %ld\n", pathconf(cwd, _PC_NAME_MAX));
   } else {
       perror("getcwd() error");
       return -1;
   }
   return 0;
}
