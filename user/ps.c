#include "types.h"
#include "pstat.h"
#include "stat.h"
#include "user.h"


#define NPROC 64 //implementation for proc
struct proc
{
    int pid;
    int ticks;
    int tickets;
    int inuse;
}

//int
main(int argc, char *argvv[])
{
    int x;
    struct proc ptable[NPROC];
    struct proc *p;

    x=getpinfo(NPROC* sizeof(struct proc), &ptable);
        if(x!=0)
        {
            printf(1,"Could Not Get Ptable");
        }

    p = &ptable[0];

    while (p != &ptable[NPROC])
    {
            printf(1, "%d", p->pid);
            printf(1, "%d", p->ticks);
            printf(1, "%d", p->tickets);
            printf(1, "%d", p->inuse); 
            p++;
    }
    exit();
}