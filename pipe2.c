#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/wait.h>
#include<errno.h>
#include<string.h>
int main(){
  int pipefd[2];
  int ret=pipe(pipefd);
  if(ret<0){
    perror("pipe errno");
    return -1;
    
  }
  int pid1=fork();
  if(pid1==0){
  //child ps-ef
  dup2(pipefd[1],1);
  execlp("ps","ps","-ef",NULL);
  
  }
  int pid2=fork();
  if(pid2==0){
  //child2 grep ssh
  dup2(pipefd[0],0);
  char buf[1111]={0};
 read(0, buf, 1024);
 printf("%s",buf);
  }
waitpid(pid1,NULL,0);
waitpid(pid2,NULL,0);
  return 0;
}
