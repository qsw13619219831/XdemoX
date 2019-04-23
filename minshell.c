#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/wait.h>

int main(){
  while(1){
  printf("[qsw13619219831@localhost ~]$");
  char buf[100]={0};
  gets(buf);
  char*ptr;
  char*hehe[100]={NULL};
 int i=0;
  
 ptr=strtok(buf," ");
 while(ptr!=NULL){
   hehe[i++]=ptr;
   ptr=strtok(NULL," ");
}
    
int pid =fork();
if(pid<0){

  printf("create process erro");
}
else if(pid==0){
  execvp(hehe[0],hehe);
}
int ret=0;
wait(&ret);

}
}
