#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
   printf("uid del usuario: %d\n", getuid()); 
   printf("euid del usuario: %d\n", geteuid());
   return 0;
}
