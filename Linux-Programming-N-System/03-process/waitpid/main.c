#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])  
{
    pid_t child_pid;                
    int status, rv;

    child_pid = fork();         

    if (0 == child_pid)
    {       /* Tiến trình con */
        printf("Im the child process (B)\n");
        printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
        sleep(5);
        exit(0); // Tiến trình con kết thúc với status code 0 sau 5s
    } 
    else
    {                    /* Tiến trình cha */
        printf("Im the parent process (A)\n");
        printf("My PID is: %d\n", getpid());
        rv = waitpid(-1, &status, NULL);
        if (rv == -1)
        {
            perror("waitpid() error\n");
        }
        else
        {
            if (WIFEXITED(status))
            {
                printf("Child exited with status: %d\n", WEXITSTATUS(status));
                printf("Pid of the terminated process: %d\n",rv);
            }
        }
    }

    return 0;
}
