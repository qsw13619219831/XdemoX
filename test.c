#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
void sigcb(int signo){

   int*p=NULL;
  printf("%d\n",*p);
  sleep(1);
printf("SIGSEGV sigcb here!\n");
}

int main(){
  signal(SIGSEGV, sigcb);
   int*p=NULL;
  printf("%d\n",*p);
 // kill(getpid(),SIGSEGV);
  //将解引用空指针改为 调用段错误信号
 
  
  
  
  
  
  
  
  //int ret=fork();
  //if(ret<0){
  // printf("create erro?!");
  //}
  //else if(ret==0){
//kill(getpid(),SIGSEGV);

// while(1){
//sleep(1);
//printf("\n");

  //   sigemptyset(&srt);
   //  sigset_t srt;
 // sigfillset(&srt);
 // sigprocmask(SIG_BLOCK,&srt,NULL);

  }

