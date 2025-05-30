#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char *argv[]){
    void *stack = malloc(4096);

    int pid = clone(stack);
    printf("pid: %d\n", pid);
    if(pid == 0)
    {
        printf("Child thread!\n");
        exit(0);
    }
    else
    {
        wait(0);
        printf("Parent process!\n");
    }
    

    return 0;
}
