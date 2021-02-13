#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
   for (int ret= 1; ret <= 255; ret++){
   	errno = ret; 
   	printf("%d, %s\n", errno, strerror(errno));
   }
   return 0;
}
