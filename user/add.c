#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "./user.h"

int main(int argc, char *argv[])
{

  if(argc!= 3){
    printf("Error provide only two numbers\n");
    exit(0);
  }
  int n1 = atoi(argv[1]);
  int n2 = atoi(argv[2]);
  int sum = n1 + n2;
  printf("Sum of %d and %d is %d\n", n1, n2, sum);

  exit(0);
}
