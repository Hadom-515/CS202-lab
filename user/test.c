#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int n=0;
    if(argc >=2) n=atoi(argv[1]);
    printf("Say hello to kernel %d\n",n);
    printf("The number of process = %d\n", sysinfo(0));
    printf("The number of syscalls = %d\n", sysinfo(1));
    printf("The number of free pages = %d\n", sysinfo(2));
    hello(n);
    exit(0);
}