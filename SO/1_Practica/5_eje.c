#include <sys/utsname.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
   int ret = 0;
   struct utsname buf;
   ret = uname(&buf);
   if (ret < 0)
   	printf("%d, errno info: %s\n", ret, strerror(errno));
   else {
   	printf("sysname: %s\n", buf.sysname);
   	printf("nodename: %s\n", buf.nodename);
   	printf("release: %s\n", buf.release);
   	printf("version: %s\n", buf.version);
   	printf("machine: %s\n", buf.machine);
   }
   return ret;
}
