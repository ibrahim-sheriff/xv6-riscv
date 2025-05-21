//2.6
// This C program calls the `randd` system call 10 times to generate and print pseudo-random numbers, then exits.
#include "kernel/types.h"
#include "user/user.h"

int main(void) {
  for(int i = 0; i < 10; i++) {
    printf("rand: %d\n", randd());
  }
  exit(0);
}
