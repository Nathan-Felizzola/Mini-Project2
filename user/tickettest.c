#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[]) //taking in arguments
{
    int pid; //creating int pid
    for(int i = 0; i < 5; i++) //for loop loops from 0 to 5 and then increments
    {
        pid = fork(); //makes pid to fork
            if(pid == 0) //if pid is 0
            {
                settickets(i*10); //set the tickets to i*10
                for(;;); //for loop keeps running/iterating
            }
    }
    exit; 
}