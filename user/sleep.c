#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "./user.h"

int main(int argc, char *argv[])
{
int sleeptime  = atoi(argv[1]);
printf("Starting sleep for %d seconds\n", sleeptime);
sleep(sleeptime);
printf("Finished sleeping for %d seconds\n", sleeptime);
}
