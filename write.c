#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
  int fd =open("haha.txt",O_WRONLY|O_CREAT|O_APPEND);
  char buf[100]="dddddddddddddddddheheheheheheiiiiiiisisiwksii";
  ssize_t a;
  a=write(fd,buf,10);
printf("%d\n",a);

}
