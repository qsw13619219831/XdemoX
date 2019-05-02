#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
  while(1){
    printf("[qsw13619219831@localhost ~]$");
    char buf[100]={0};
    gets(buf);
    char*ptr;
    char*hehe[100]={NULL};
    int k=0;
    int i=0;

    ptr=strtok(buf," ");
    while(ptr!=NULL){
      hehe[i]=ptr;
      ptr=strtok(NULL," ");
      if(*hehe[i]=='>'){
        k++;
        hehe[i]=NULL;
        break;
      }
       i++;

    }

    int pid =fork();
    if(pid<0){

      printf("create process erro");

    }
    else if(pid==0){
      if(k>0){
        //需要重定向;
        int file =open(ptr,O_RDWR);
       dup2(file,1);
      }
      execvp(hehe[0],hehe);

    }
    int ret=0;
    wait(&ret);


  }

}
