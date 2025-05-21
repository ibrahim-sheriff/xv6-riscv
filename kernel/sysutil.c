struct datetime {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
};

#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "memlayout.h"
#include "proc.h"

extern uint ticks; // <- Add this line- this is the global ticks variable

#define TICKS_PER_SECOND 100 // Assuming 100Hz timer

#define KERNBASE 0x80000000L // Kernel base address
#define CLINT_MTIME_VA (KERNBASE + 0x200bff8UL) // CLINT memory-mapped I/O address

static uint64 randd_seed = 1;

extern int kbdint_count;

uint64
sys_kbdint(void){
  return kbdint_count;
}

static uint64
lcg_randd(void)
{
  randd_seed = randd_seed * 6364136223846793005ULL + 1;
  return (uint32)(randd_seed >> 32); // Return a 32-bit pseudo-random number
}

uint64
sys_randd(void)
{
  return lcg_randd();
}

// ----------- datetime system call -----------
#ifndef BOOT_EPOCH // Set the epoch time to 1 Jan 1970
#define BOOT_EPOCH 1715852800 // fallback, should be set by Makefile
#endif
//2.5 Convert Unix timestamp to datetime structure
static void
unix_to_datetime(uint64 timestamp, struct datetime *dt)
{
  static const int days_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  int seconds_per_day = 86400;
  int days = timestamp / seconds_per_day;
  int secs_today = timestamp % seconds_per_day;

  dt->hour = secs_today / 3600;
  dt->minute = (secs_today % 3600) / 60;
  dt->second = secs_today % 60;

  int year = 1970;
  while (1) {
    int leap = (year%4==0 && (year%100!=0 || year%400==0));
    int ydays = leap ? 366 : 365;
    if (days >= ydays) {
      days -= ydays;
      year++;
    } else break;
  }
  dt->year = year;

  int month = 0;
  while (1) {
    int dim = days_in_month[month];
    if (month == 1 && (year%4==0 && (year%100!=0 || year%400==0)))
      dim++;
    if (days >= dim) {
      days -= dim;
      month++;
    } else break;
  }
  dt->month = month + 1;
  dt->day = days + 1;
}
//2.5 Get current date and time
// This function retrieves the current date and time since system boot
// and stores it in a datetime structure, which includes year, month,
// day, hour, minute, and second. The function uses the ticks variable
// to calculate the number of seconds since boot, and then converts
uint64
sys_datetime(void)
{
  uint64 user_addr;
  argaddr(0, &user_addr);

  // Use xv6's ticks variable, which is incremented at 100Hz
  extern uint ticks;
  uint64 seconds_since_boot = ticks / TICKS_PER_SECOND;
  uint64 current_timestamp = BOOT_EPOCH + seconds_since_boot;

  struct datetime dt;
  unix_to_datetime(current_timestamp, &dt);

  if(copyout(myproc()->pagetable, user_addr, (char*)&dt, sizeof(dt)) < 0)
    return -1;
  return 0;
}


uint64
sys_countsyscall(void)
{
  return syscall_count;
}
