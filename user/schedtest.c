#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

// example usage:
// $ schedtest 0   # Test Round Robin
// $ schedtest 1   # Test FCFS
// $ schedtest 2   # Test Priority

int main(int argc, char *argv[]) {
  int pid;
  int k, nprocess = 10;
  int z, steps = 1000000;
  char buffer_src[1024], buffer_dst[1024];

  if(argc != 2) {
    printf("Usage: schedtest <mode>\n");
    printf("  0: Round Robin\n  1: FCFS\n  2: Priority\n");
    exit(1);
  }

  int mode = atoi(argv[1]);
  if(setscheduler(mode) < 0) {
    printf("Invalid scheduler mode: %d\n", mode);
    exit(1);
  } else {
    printf("Scheduler mode set to %d\n", mode);
  }

  for (k = 0; k < nprocess; k++) {
    // For FCFS, sleep to ensure different creation times
    if(mode == 1)
      sleep(2);

    pid = fork();
    if (pid < 0) {
      printf("%d failed in fork!\n", getpid());
      exit(0);
    }
    else if (pid == 0) {
      // child
      if(mode == 2)
        setpriority(getpid(), k); // Assign priorities for Priority mode

      // Acquire print lock
      while(open("print.lock", O_CREATE | O_EXCL) < 0) //this line
        ; // spin until lock acquired

      // Now safe to print
      printf("[pid=%d] created with priority %d\n", getpid(), k);

      // Release print lock
      unlink("print.lock");

      for (z = 0; z < steps; z += 1) {
        memmove(buffer_dst, buffer_src, 1024);
        memmove(buffer_src, buffer_dst, 1024);
      }
      exit(0);
    }
  }

  for (k = 0; k < nprocess; k++) {
    pid = wait(0);
    printf("[pid=%d] terminated\n", pid);
  }
  printmetrics();
  exit(0);
}
