#include<stdio.h>
int main(){

FILE*fd=fopen("hehe.txt","r+");
//FILE*fd=fopen("hehe.txt","w");
//FILE*fd=fopen("hehe.txt","w+");
//FILE*fd=fopen("hehe.txt","a");
//FILE*fd=fopen("hehe.txt","a+");
char buf[100]="father mother go to work ,im going to school!";
size_t a=fwrite(buf,4,4,fd);
printf("%d\n",a);
}
