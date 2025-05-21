#include "types.h"

extern int syscall_count;

uint64
sys_countsyscall(void)
{
  return syscall_count;
}
