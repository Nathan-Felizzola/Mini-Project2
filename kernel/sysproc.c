#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"
#include "pstat.h"
#include "rand.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
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
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
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
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//PROJECT2
int sys_settickets(void)
{
 int num_tickets; 
 if(argint(0,&num_tickets)<0)
 {
   return settickets(num_tickets); 
 } 
 proc->tickets=num_tickets;
 return num_tickets;
}

//PROJECT2
int sys_getpinfo(void)
{
  struct pstat* pst; 
  if(argptr(0,(void*)&pst, sizeof(*pst)<0))
    return getpinfo(pst);
  return 0;
}

// int getpinfo(struct pstat* pInfo)
// {
//   int i = 0
//   acquire(&ptable.lock);
//   for(p=ptable.proc; p < &ptable.proc[NPROC]; p++)
//   {
//     if(p->state == ZOMBIE || p->state == EMBRYO)
//     {
//       continue;
//     }
//     if(p->state == UNUSED)
//     {
//       pInfo->inuse[i]=0;
//     }
//     else
//     {
//       pInfo->inusue[i]=1;
//     }
//     pInfo->pid[i] = p->pid;
//     pInfo->tickets[i]=p->procTickets;
//     pInfo->ticks[i]=p->numTicks;
//   }
//   release(&ptable.lock);
//   return 0; 
// }