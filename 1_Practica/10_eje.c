#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pwd.h>

int main() {
   uid_t uid = getuid(); 
   
   struct passwd *pass= getpwuid(uid);

   printf("Username: %s\n", pass->pw_name);
   printf("Home: %s\n", pass->pw_dir);
   printf("Descripción del usuario: %s\n",pass->pw_gecos);
   return 0;
}
