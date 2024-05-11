#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void signal_hanlder(int signum)
{
	printf("Im in func()\n");
	wait(NULL);
}

int main(int argc, char const *argv[])  
{
  
    pid_t child_pid;                
    child_pid = fork();         
   
        if (0 == child_pid)
         {       /* Process con */
            
            printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
            
         } else  
         {                    /* Process cha */
            
			signal(SIGCHLD, signal_hanlder );
			printf("I am Parent\n");
			while(1);
	       
         }
        


}
