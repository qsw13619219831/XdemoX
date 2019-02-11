#include<stdio.h>
void zuoxuan(char *p,int x){
    char tem=*(p);
 for(int i=0;i<x;i++){
   *(p+i)=*(p+i+1);
 }
  *(p+(x-1))=tem;
}
void xunhuan(char *p,int x,int y){
  for(int i=0;i<y;i++){
    zuoxuan(p,x);
  }
}
int main(){
char arr[]={'a','b','c','d'},*p;
p=arr;
int x=sizeof (arr)/sizeof (char);
xunhuan(p,x,2);
int i=0;
  for(i=0;i<5;i++){
    printf("%c",arr[i]);
  }
printf("\n");
return 0;
}
