#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])  
{
    /* code */
    pid_t child_pid;                
    int a = 0;               
    printf("Gia tri khoi tao cua a: %d\n", a);

    child_pid = fork();         
   
        if (0 == child_pid)
         {       /* Process con */
            printf("\nIm the child process (B), a: %d\n", ++a);
            printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
            
         } else  
         {                    /* Process cha */
            printf("\nIm the parent process (A), a: %d\n", a);
            printf("My PID is: %d\n", getpid());
	       
         }
        

    return 0;
}
