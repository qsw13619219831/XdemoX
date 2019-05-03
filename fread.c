#include<stdio.h>



int main(){

FILE*fd=fopen("hehe.txt","r");
//FILE*fd=fopen("hehe.txt","r+");
//FILE*fd=fopen("hehe.txt","w+");
char buf[100]={0};
size_t a;
a=fread(buf,2,2,fd);

printf("%s\n",buf);
printf("%d\n",a);
}
