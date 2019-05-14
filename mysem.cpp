#include<iostream>
#include<queue>
#include<semaphore.h>
#include<pthread.h>
using namespace std;


class blockqueue{
  public:
  blockqueue(int capcacity=1){
  _capcacity=capcacity;
  sem_init(&_block,0,1);
  sem_init(&_prodcutor,0,10);
  sem_init(&_consumer,0,0);
  }
  ~blockqueue(){
    _capcacity=0;
    sem_destroy(&_block);
    sem_destroy(&_prodcutor);
    sem_destroy(&_consumer);

  }
  bool queue_push(int data){
  productorwait();
  queuelock();
  _blockqueue.push(data);
  cout<<"i have push a data"<<data<<endl;
  queueunlock();
  consumerwake();
  return true;
  }
  
  bool queue_pop(int *data){
    consumerwait();
    queuelock();
    *data=_blockqueue.front();
    _blockqueue.pop();
    cout<<"consumer have read a data"<<*data<<endl;
    queueunlock();
    productorwake();
    return true;
  }
  private:
  void queuelock(){
    sem_wait(&_block);
  }
  void queueunlock(){
    sem_post(&_block);
  }
  void productorwait(){
    sem_wait(&_prodcutor);
  }
  void productorwake(){
    sem_post(&_prodcutor);
  }
  void consumerwait(){
    sem_wait(&_consumer);
  }
  void consumerwake(){
    sem_post(&_consumer);
  }

  private:
  queue<int>_blockqueue;
  int _capcacity;
  sem_t _block;
  sem_t _prodcutor;
  sem_t _consumer;
};
void* th_consumer(void *arg){
  blockqueue*q=(blockqueue*)arg;
  while(1){
    int data=0;
    q->queue_pop(&data);
  }

  return NULL;
}
void* th_productor(void*arg){
  blockqueue*p=(blockqueue*)arg; 
  int i=0;
  while(1){
    p->queue_push(i++);
  }
  return NULL;
}
int main(){
  blockqueue q;
  pthread_t ctid[4],ptid[4];
  for(int i=0; i < 4;i++){
    int ret=pthread_create(&ctid[i],NULL,th_consumer,(void*)&q);
  }
  for(int i=0; i < 4;i++){
    int ret=pthread_create(&ptid[i],NULL,th_productor,(void*)&q);
  }
  for(int i=0;i < 4;i++){
    pthread_join(ctid[i],NULL);
  }
  for(int i=0;i < 4;i++){
    pthread_join(ptid[i],NULL);
  }
  return 0;
}

