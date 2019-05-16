#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<stdio.h>
#include<queue>
#include<pthread.h>
using std::cout;
using std::endl;
typedef bool (*task_callback)(int data);
bool deal_administor(int data)
{
  srand(time(NULL));
  int n =rand()%5;
  printf("thread:%p chulishuju:%d   chulile %dmiao\n",
      pthread_self(),data,n);
  sleep(n);
  return true;
}


class Task
{
  public:
    Task(){
    }
    ~Task(){
    }
  public:
    void settask(int data,task_callback handler){
      _handler=handler;
      _data=data;
    }
    bool taskrun(){
      return _handler(_data);
    }

  private:
    task_callback _handler;
    int _data;
};

#define MAX_THR 5
#define MAX_QUE 10

class poolqueue
{
  public:
  poolqueue(){
    pthread_mutex_init(&mutex1,NULL);
    pthread_cond_init(&productor,NULL);
    pthread_cond_init(&consumer,NULL);
  }
  ~poolqueue(){
    pthread_mutex_destroy(&mutex1);
    pthread_cond_destroy(&productor);
    pthread_cond_destroy(&consumer);
  }

  bool initqueue(int max_thr=MAX_THR,int max_que=MAX_QUE)
  {    
    _quit_flag=false;
    _max_thr=max_thr;
    _cur_thr=max_thr;
    _capacity=max_que;
    int ret;
    pthread_t tid;
    for(int i=0;i < _max_thr;i++){
      ret=pthread_create(&tid,NULL,thr_start,(void*)this);
      if(ret!=0){
        cout<<"thread create erro!"<<endl;
        return false;
      }
      pthread_detach(tid);
    }
    return true; 
  }  

  bool queuepush(Task &task){
    if(_quit_flag==true){
      return false;
    }
    while(1){
      queuelock();
      while(queueisfull()){
        productorwait();
      }
      _mypoolq.push(task);
      consumerwakeup();
      queueunlock();
      return true;
    }
  }
  void consumerwait(){
    if(_quit_flag==true){
      pthread_mutex_unlock(&mutex1);
      printf("finsh i quit %p\n",pthread_self());
      _cur_thr--;
      pthread_exit(NULL);
    }
    pthread_cond_wait(&consumer,&mutex1);
  }

  void consumerwakeup(){
    pthread_cond_signal(&consumer);
  }

  void productorwait(){
    pthread_cond_wait(&productor,&mutex1);
  }

  void productorwakeup(){
    pthread_cond_signal(&productor);
  }

  void conwakeupall(){
    cout<<"read quit ,wake up all"<<endl;
    pthread_cond_broadcast(&consumer);
  }
  void queuepop(Task*task){
    *task=_mypoolq.front();
    _mypoolq.pop();

  }

  void queuelock(){
    pthread_mutex_lock(&mutex1);
  }

  void queueunlock(){
    pthread_mutex_unlock(&mutex1);
  }

  bool queueisfull(){
    return (_capacity==_mypoolq.size());
  }

  bool QueueIsEmpty(){
    return _mypoolq.empty();
  }

  void quitthread(){
    if(_quit_flag!=true){
      _quit_flag=true;
    }
    while(_cur_thr > 0){
      conwakeupall();
      sleep(1);
    }
    return ;
  }

  static void *thr_start(void*arg){
    poolqueue *pool=(poolqueue *)arg;
    while(1){
      pool->queuelock();
      while(pool->QueueIsEmpty()){
        pool->consumerwait();
      }
      Task task;
      pool->queuepop(&task);
      pool->productorwakeup();
      pool->queueunlock();
      task.taskrun();
    }
    return NULL;
  }

  private:
  pthread_mutex_t mutex1;
  pthread_cond_t productor;
  pthread_cond_t consumer;
  std::queue<Task> _mypoolq;
  int _max_thr;//最大
  int _cur_thr;
  int _quit_flag;
  int _capacity; 
};

int main()
{
  poolqueue pool;
  pool.initqueue();
  Task task[10];
  for(int i=0;i < 100;i++ ){
    task[i].settask(i,deal_administor);
    pool.queuepush(task[i]);
  }
  pool.quitthread();
  return 0;
}
