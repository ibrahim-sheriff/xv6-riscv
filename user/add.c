// Ashraf

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if(argc < 4){
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int sum = num1 + num2;
    printf("sum = %d\n", sum);
  } else {
    printf("error can only take 2 integers \n");
    exit(0);
  }
  exit(0);
}
