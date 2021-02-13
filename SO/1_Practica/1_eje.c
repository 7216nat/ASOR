#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
   int ret = 0;
   ret = setuid(0);
   if (ret < 0)
   	perror("error on setuid()");
   return 0;
}

