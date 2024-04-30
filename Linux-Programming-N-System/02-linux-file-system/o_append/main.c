#include<stdio.h> 
#include<string.h> 
#include<unistd.h> 
#include<fcntl.h> 

int main (void) 
{ 
    int fd; //file descriptor
    int numb_read, numb_write;
    char buf1[12] = "hello world\n"; 
  
    // assume foobar.txt is already created 
    fd = open("hello.txt", O_WRONLY | O_APPEND | O_CREAT, 0667);         
    if (-1 == fd) { 
	printf("open() hello.txt failed\n");
    }      
  
    lseek(fd, 0, SEEK_SET);
    write(fd, "AAA", strlen("AAA"));
    
    close(fd); 
  
    return 0; 
} 
