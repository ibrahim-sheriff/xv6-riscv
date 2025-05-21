//2.5
// This C program retrieves the current date and time using the `datetime` system call, stores it in a `datetime` structure, and prints it in the format "year-month-day hour:minute:second", exiting with an error if the system call fails.
#include "kernel/types.h"
#include "user/user.h"

int main(void) {
  struct datetime dt;
  int ret = datetime(&dt);
  if (ret < 0) {
    fprintf(2, "Error: datetime syscall failed\n");
    exit(1);
  }
  printf("Current date and time: %d-%d-%d %d:%d:%d\n",
         dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);
  exit(0);
}
