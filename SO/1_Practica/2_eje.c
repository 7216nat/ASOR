#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
   int ret = 0;
   ret = setuid(0);
   if (ret < 0)
   	printf("%d, errno info: %s\n", ret, strerror(errno));
   return 0;
}
