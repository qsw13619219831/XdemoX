#include<stdio.h>
#include <pthread.h>
#include<unistd.h>
#include<stdlib.h>
//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
//int pthread_mutex_lock(pthread_mutex_t *mutex);
// int pthread_cond_signal(pthread_cond_t *cond);
pthread_mutex_t mutex1;
pthread_cond_t cond1;
int noddles =1;

void*bossfunction(void* arg){
 while(1){
pthread_mutex_lock(&mutex1);
    while(noddles==1){

pthread_cond_wait(&cond1,&mutex1);
    }
printf("do a noddles!\n");
noddles+=1;
pthread_mutex_unlock(&mutex1);
pthread_cond_signal(&cond1);
 }
return NULL;


}
void*coustorm(void* arg){
while(1){
pthread_mutex_lock(&mutex1);
  while(noddles==0){
pthread_cond_wait(&cond1,&mutex1);
  }
printf("i have eat,one more\n");
 noddles-=1;
pthread_mutex_unlock(&mutex1);
pthread_cond_signal(&cond1);
}


return NULL;
}

int main(){

pthread_t boss2;
pthread_t boss1;

pthread_t coustom2;
pthread_t coustom1;
pthread_mutex_init(&mutex1,NULL);
pthread_cond_init(&cond1,NULL);
int ret= pthread_create(&boss1, NULL,bossfunction,NULL); 
int ret2= pthread_create(&boss2, NULL,bossfunction,NULL); 
if(ret<0){
perror("boss cretate erro:");
}
int ret3= pthread_create(&coustom1, NULL,coustorm,NULL);
int ret4= pthread_create(&coustom2, NULL,coustorm,NULL);
if(ret2<0){
  perror("coustom1 create erro");
}

int jon=pthread_join(boss1,NULL);
int jon2=pthread_join(boss2,NULL);
if (jon<0){
  perror("boss wait erro");
}
int jon3=pthread_join(coustom1,NULL);
int jon4=pthread_join(coustom2,NULL);
if(jon2<0){
perror("coustom wait erro");  
}
pthread_mutex_destroy(&mutex1);
pthread_cond_destroy(&cond1);
}
