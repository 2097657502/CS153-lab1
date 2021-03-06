#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  int status;
  if(argint(0, &status) < 0){
     return -1;
  }
  exit(status);
  return 0; // not reached because always exits with status
}

// change. assignment 1 part b.
int
sys_wait(void)
{ 
  int* status;
  if(argptr(0,(char**) &status, sizeof(*status) < 0)){
	return -1;//Checking to see if status exists
  }
		
  //argptr() is in syscall.c
  return wait(status);
}

int 
sys_waitpid(void)
{
  int pid;
  int options;
  int* status;
  
  if(argint(0, &pid) < 0){
	return -1; //Checking to see if pid exists, first parameter passed in
  }

  if(argptr(1,(char**) &status, sizeof(*status) < 0)){
	return -1; //Checking to see if status exists, second parameter passed in
  }
  if(argint(2, &options) < 0){
	return -1; //Checking to see if the options exists, third parameter in
  }
  
  return waitpid(pid, status, options);
  
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
int
sys_add(void)
{
  int a=1;
  int b=2021;
  return a+b;
}
//int                // assignment 1 part a
//sys_exit(int)
//{
//  int a;
//  if(argint(0,&a)<0){
//    return -1;
//  }
//  return exit(a);
//}

//lab2 part 1, add a handler system to the priority system call to update the data
int
sys_priority(void)
{
  int p;
  if(argint(0, &p)<0){
    return -1;
  }
  return priority(p);
}
