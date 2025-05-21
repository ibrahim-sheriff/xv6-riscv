#include "kernel/types.h"
#include "user/user.h"

int main(void) {
  printf("Total syscalls since boot: %d\n", countsyscall());
  exit(0);
}
