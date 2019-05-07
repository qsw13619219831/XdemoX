#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<unistd.h>
#include<string.h>
int main(){
  struct msgbuf{

    long  mtype;
    char mtext[255];

  };
  
struct msgbuf a;
   int ret= msgget(4,IPC_CREAT|0666);
  if (ret>=0){
         printf("mq is create!\n");
        
   }
  while(1){
    memset(&a,1,sizeof(a));
    sleep(1);
int size= msgrcv(ret, &a,sizeof(a), 0, 0);
if(size<0){
  perror("get erro");
}
printf("%s",a.mtext);
if (msgctl(ret, IPC_RMID, 0) != -1){
 printf("delete msg success\n");


}

}
}
