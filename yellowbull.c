#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
int ticket=100;
 pthread_mutex_t mutex;


void* thr_start(void*arg){
  pthread_detach(pthread_self());
  while(1){
  pthread_mutex_lock(&mutex);
if(ticket>0){
printf("%d bull get the ticket,ticket no is%d\n",(int)arg,ticket);
ticket --;
}
else{
pthread_mutex_unlock(&mutex);
pthread_exit(NULL);
}
pthread_mutex_unlock(&mutex);
  }
return NULL;
}


int main(){
  //创建线程
 pthread_mutex_init(&mutex,NULL); 
  pthread_t tid[4];
  for(int i=0;i<4;i++){
int ret= pthread_create(&tid[i], NULL,thr_start,(void*)i);
 printf("%d",ret);
  }
//  for (int i = 0; i < 4; i++) {
 //     pthread_join(tid[i], NULL);
          
 // }
 pthread_mutex_destroy(&mutex);
return 0;}
