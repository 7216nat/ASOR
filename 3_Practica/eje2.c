#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  int pid = getpid();
  int sched = sched_getscheduler(pid);

  switch (sched) {
    case SCHED_OTHER:
      printf("SCHEDULER: OTHER\n");
    break;
    case SCHED_FIFO:
      printf("SCHEDULER: FIFO\n");
    break;
    case SCHED_RR:
      printf("SCHEDULER: RR\n");
    break;
    default:
      printf("SCHEDULER: ERROR\n");
    break;
  }

  struct sched_param param;
  sched_getparam(pid,&param);
  printf("PRIORIDAD: %d\n", param.sched_priority);
  printf("MAX PRIOR: %d\n", sched_get_priority_max(sched));
  printf("MIN PRIOR: %d\n", sched_get_priority_min(sched));

}