#include<iostream>
#include<queue>
#include<pthread.h>

using namespace std;

class Blockqueue
{
  public:
  Blockqueue(int cap=1):capacity(cap){
    pthread_cond_init(&boss,NULL);
    pthread_cond_init(&costurm,NULL);
    pthread_mutex_init(&mutex1,NULL);
     
  }
   
 
  ~Blockqueue(){
    pthread_cond_destroy(&boss);
    pthread_cond_destroy(&costurm);
    pthread_mutex_destroy(&mutex1);
  }
  bool Bqueuepush(int data){
    Bqueuelock();
      while(Bqueueisfull()){
      bosswait();
      }
      a.push(data);
      cout<<"i have push a data"<<endl;
      costurmwakeup();
      Bqueueunlock();
      return true;
  }
  bool Bqueuepop(int* data){
    Bqueuelock();
    while(Bqueueisempty()){
      costurmwait();
    }
    *data=a.front();
    a.pop();
    cout<<"i have read a data "<<*data<<endl;
    bosswakeup();
    Bqueueunlock();
    return true;
  }
  private:
  void Bqueuelock(){
    pthread_mutex_lock(&mutex1);
  }
  void Bqueueunlock(){
    pthread_mutex_unlock(&mutex1);

  }
  void costurmwait(){
    pthread_cond_wait(&costurm,&mutex1);

  }
  void costurmwakeup(){
    pthread_cond_signal(&costurm);
  }
  void bosswait(){
    pthread_cond_wait(&boss,&mutex1);
  }
  void bosswakeup(){
    pthread_cond_signal(&boss);
  }
  bool Bqueueisfull(){
   return (a.size()==capacity);
  }
  bool Bqueueisempty(){
    return (a.empty());
  }
  private:
  pthread_mutex_t mutex1;
  pthread_cond_t costurm;
  pthread_cond_t boss;
  queue<int> a;
  int capacity;
};
  void*th_coustorm(void*arg)
{
  Blockqueue *q=(Blockqueue*)arg;
  while(1){
    int data;
    q->Bqueuepop(&data);
    }
  return NULL;
}
  void*th_boss(void*arg)
{
  int i=0;
  Blockqueue*q=(Blockqueue*)arg;
  while(1){
    q->Bqueuepush(i++);
  }
  return NULL;
}


int main(int argc,char*argv[])
{
  pthread_t btid[4],ctid[4];
  Blockqueue q;
  int ret;
  for(int i=0;i < 4;i++){
  ret=pthread_create(&ctid[i],NULL,th_coustorm,(void*)&q);
      if(ret!=0){
      cout<<"pthread create error\n"<<endl;
      }
  }

  for(int i=0;i < 4;i++){
   ret=pthread_create(&btid[i],NULL,th_boss,(void*)&q);
   if(ret!=0){
      cout<<"pthread create error\n"<<endl;
   }
  }
  for(int i=0; i < 4;i++){
    pthread_join(ctid[i],NULL);
  }
  for(int i=0;i < 4;i++){
    pthread_join(btid[i],NULL);
  }
  return 0;
}
