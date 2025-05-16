#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char *argv[]){
    
        sched_statistics();
        fork();
        for(int i=0;i<5;i++){
            if(getpid()<4){
                sched_tickets(i*100);
            }
            else{
                sched_tickets(10000-i*100);
            }
            sched_statistics();
        }


    return 0;
}