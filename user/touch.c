#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[]) {
  int fd;
  struct stat st;

  if(argc != 2){
    printf("Usage: touch filename\n");
    exit(1);
  }

  if (stat(argv[1], &st) == 0) {
      fprintf(2, "touch: %s already exists\n", argv[1]);
      exit(1);
  }

  fd = open(argv[1], O_CREATE | O_WRONLY);
  if (fd < 0) {
    fprintf(2, "touch: cannot create %s\n", argv[1]);
    exit(1);
  }
  close(fd);
  exit(0);
}
