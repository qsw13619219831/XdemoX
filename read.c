#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main(){

//open/read/write/close

 int a= open("hehe.txt",O_RDONLY);
 ssize_t lenth;
 char arr[100]={0};
lenth= read(a,arr,sizeof(char)*100);
printf("%s\n",arr);

printf("%d\n",lenth);

}
