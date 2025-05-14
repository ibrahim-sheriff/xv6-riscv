#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
// move shahd.txt folder/shahd.tx
int main(int argc, char *argv[]) {
  if(argc != 3){
    printf("Usage: mv source target\n");
    exit(1);
  }

  if(link(argv[1], argv[2]) < 0){
    printf("mv: cannot link %s to %s\n", argv[1], argv[2]);
    exit(1);
  }

  unlink(argv[1]);
  exit(0);
}
