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
 int ret= msgget(4,IPC_CREAT|0666);
if(ret<0){}
struct msgbuf a;
a.mtype=1;
strcpy(a.mtext,"ni hao a");
while(1){
  sleep(1);
 if (ret>=0){
   printf("mq is create!\n");
 }
int ret2= msgsnd( ret, &a, sizeof(a),0);
if(ret2>=0){
  printf("send succed!\n");
if(ret2<0){
  perror("snd erro:");}
}
}
}
