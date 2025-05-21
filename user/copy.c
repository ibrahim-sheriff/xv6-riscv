#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

char buf[512];

int main(int argc, char *argv[]) {
  int fd0, fd1, n;

  if(argc != 3){
    printf("Usage: cp source dest\n");
    exit(1);
  }

  fd0 = open(argv[1], 0);
  if(fd0 < 0){
    printf("cp: cannot open %s\n", argv[1]);
    exit(1);
  }

  fd1 = open(argv[2], O_CREATE | O_WRONLY);
  while((n = read(fd0, buf, sizeof(buf))) > 0){
    write(fd1, buf, n);
  }

  close(fd0);
  close(fd1);
  exit(0);
}
