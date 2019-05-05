/*匿名管道的基本使用
 *int pipe(int pipefd[2])
 * */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
int main(){
  int pipefd[2];
  int ret=pipe(pipefd);
  if(ret<0){
    perror("pipe error");
    return -1;
  }
  int pid=fork();
  if(pid<0){
    perror("fork error");
    return -1;
  }
  else if(pid==0){
//child write
  char*ptr="nihao~~";
  write(pipefd[1],ptr,strlen(ptr));
  }
  else{
//parent read
  char buf[1024]={0};
  read(pipefd[0],buf,1023);
  printf("read buf:[%s]\n",buf);
  }
  return 0;
  

}
