#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64 sys_hello(void)
{
  int n;
  argint(0,&n);
  print_hello(n);
  return 0;
}
//CS202 - Lab1 total syscalls
extern int total_syscalls;

uint64 sys_sysinfo(void)
{
  int n;
  argint(0,&n);
  if(n==0){
    return procCount();
  }
  else if(n==1){
    return total_syscalls;
  }
  else if(n==2){
    return freePageCount();
  }
  else
    return -1;
  return 0;
}

uint64 
sys_procinfo(void)
{
  // get this process
  struct proc* p = myproc();

  // address of user space buffer
  // to copy the process info into
  uint64 addr;
  argaddr(0,&addr);
  if(addr == 0){
    return -1;
  }

  // make similar pinfo struct in kernel space
  struct {
    int ppid;
    int syscall_count;
    int page_usage;
  } proc_info;

  // fill the struct
  proc_info.ppid = p->parent->pid;
  proc_info.syscall_count = p->syscall_count-1; // not including this syscall
  int n = p->sz/PGSIZE; // if sz not divisible by PGSIZE we are partially using one more page
  proc_info.page_usage = (p->sz%PGSIZE) ? n+1 : n;

  // copy the struct to user space address
  if(copyout(p->pagetable, addr, (char*)&proc_info, sizeof(proc_info)) < 0){
    return -1;
  }
  return 0;
}
uint64 sys_sched_statistics(void){
  print_statistics();
  return 0;
}
uint64 sys_sched_tickets(void){
  int n;
  argint(0,&n);
  struct proc* p = myproc();
  if(n<0){
    return -1;
  }
  if(n<=10000){
    p->tickets=n;
  }
  else{
    p->tickets=10000;
  }
  p->stride=10000/p->tickets;
  p->pass=p->stride;
  return 0;
}
uint64 sys_clone(void)
{
  uint64 addr;
  argaddr(0,&addr);
  clone((void*)addr);
  return 0;
}