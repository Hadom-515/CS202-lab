#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char *argv[]){
    void* test = (void *) 1000;
    clone(test);
    sched_statistics();
    return 0;
}