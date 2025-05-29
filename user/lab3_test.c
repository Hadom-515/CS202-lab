#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char *argv[]){
    void *stack = malloc(4096);

    int pid = clone(stack);
    if(pid == 0)
    {
        printf("Child thread!\n");
        exit(0);
    }
    else
    {
        printf("Parent process!\n");
        wait(0);
    }
    

    return 0;
}