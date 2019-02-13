#include<stdio.h>
int panduan(char*p,char*q,int x){
 int count =0;
  while(count<=x){
    if(*p==*q){
      int i=0;
     char *r=q;
      for( i=0;i<x;i++){
        printf("%c%c ",*p,*r);
        if(*(p)==*(r)){
          if(*(r+1)=='\0'){
           r=r-(x-1);
           p=p+1;
          }
          else{
           r=r+1;
           p=p+1;
          }
        }
        else{
          break;
        }
      }
      if(i==(x)){
        return 1;
      } 
    }
    else{
      q=q+1;
    count++;
    }
  }
  return 0;
}
int main(){
char arrs[]={'a','b','c','d'},*p;
char arrd[]={'a','c','b','d'},*q;
p=arrs;
q=arrd;
int x=sizeof(arrs)/sizeof(char);
int s=panduan(p,q,x);
printf("%d",s);
}
