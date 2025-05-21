#include "types.h"

extern int kbdint_count;

uint64
sys_kbdint(void){
  return kbdint_count;
}

uint64
sys_countsyscall(void){
  return kbdint_count;
}

uint64
sys_getppid(void){
  return kbdint_count;
}

uint64
sys_getptable(void){
  return kbdint_count;
}

uint64
sys_datetime(void){
  return kbdint_count;
}

uint64
sys_randd(void){
  return kbdint_count;
}
