#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int factorial(int n) {
  if(n <= 1)
    return 1;
  return n * factorial(n - 1);
}

int main(int argc, char *argv[]) {
  if(argc != 2){
    printf("Usage: fact number\n");
    exit(1);
  }

  int n = atoi(argv[1]);
  if(n < 0){
    printf("fact: number must be non-negative\n");
    exit(1);
  }

  printf("Factorial of %d is %d\n", n, factorial(n));
  exit(0);
}
