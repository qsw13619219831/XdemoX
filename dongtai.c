#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include<string.h>
#define person_info_max_size 200
typedef struct personinfo{
char name[1024];
char phone[1024];
}personinfo;
typedef struct addressbook{
  int shit;
  int size;;
  personinfo *infos;
}addressbook;
addressbook g_address_book;
int menu(){
  printf("===================================\n");
  printf("1.xinzen\n");
  printf("2.shanchu\n");
  printf("3.xiugai\n");
  printf("4.chazhao\n");
  printf("5.paixu\n");
  printf("6.xianshiquanbu\n");
  printf("7.qingkongquanbu\n");
  printf("0.tuichu\n");
  printf("===================================\n");
  printf("qinsghurunindexuanze:");
  int choice=0;
  scanf("%d",&choice);
  return choice;
}
void init(addressbook* addr_book){
  assert(addr_book!=NULL);
  addr_book->size=0;
  addr_book->shit=3;
 addr_book->infos= (personinfo*)malloc(sizeof(personinfo )*addr_book->shit); 

}
void addpersoninfo(addressbook* addr_book){
  assert(addr_book!=NULL);
  printf("charuyigelianxiren\n");

  if(addr_book->size>=addr_book->shit){
    printf("+++++++++++++++++++++++++++++++\n");
     addr_book->shit+=3;
     realloc(addr_book->infos,sizeof(personinfo)*addr_book->shit);
  }
  personinfo* p=&addr_book->infos[addr_book->size];
  printf("qinsghurulianxirenxingming:");
  scanf("%s",p->name);
  printf("qingshuruxinzengdelianxirendianhua:");
  scanf("%s",p->phone);
  ++addr_book->size ;


  printf("charulianxirenchenggong!\n");
}
void delpersoninfo(addressbook* addr_book){
  assert(addr_book!=NULL);
  printf("shanchulianxiren!\n");
  printf("qinshuruyaoshanchudelianxiren id:");
  int id =0;
  scanf("%d",&id);
  if(id<0||id>=addr_book->size){
  printf("ninshurudexuhaoyouwu!shanchushibai!\n");
  return;
}
  personinfo*p=&addr_book->infos[id];
  printf("ningyaoshanchudelianxirenwei[%d]%s,querenqingchuruY:",id,p->name);
  char cmd[1024]={0};
scanf("%s",cmd);
if(strcmp(cmd,"Y")!=0){
  printf("shanchucaozuoquxiao\n");
  return;
}
 personinfo*from=&addr_book->infos[addr_book->size-1];
 personinfo* to=p;
*to=*from;
--addr_book->size;
  printf("shanchuchenggong!\n");
}
void modifypersoninfo(addressbook* addr_book){
assert(addr_book!=NULL);
printf("xiugailianxiren!\n");
printf("shuruxiugai no:");
  int id=0;
scanf("%d",&id);
if(id<0||id>=addr_book->size){
  printf("nishurudexuhaocuowu!\n");
return;
}
  personinfo *p=&addr_book->infos[id];
  printf("qi ngshuruyaoxiugaidexingming:\n");
  scanf("%s",&p->name);
  printf("qingshuruyaogaidedianhua:\n");
  scanf("%s",&p->phone);
  printf("xiugaichenggong!\n");
}

void findpersoninfo(addressbook* addr_book){
assert(addr_book!=NULL);
printf("qingshuruniyaochazhaoderende xingming:");
char arr[1024]={};
scanf("%s",&arr);
for(int i=0;i<=addr_book->size;i++){
personinfo *p=&addr_book->infos[i];
if(strcmp(arr,p->name)==0){
  printf("xingmingshi:  %s\n",p->name);
  printf("dianhuashi:    %s\n",p->phone);
}

}
}
void sortpersoninfo(addressbook* addr_book){
}
void printallpersoninfo(addressbook* addr_book){
assert(addr_book!=NULL);
printf("xianshisuoyoulianxiren!\n");
for(int i=0;i<addr_book->size;++i){
  personinfo *p=&addr_book->infos[i];
  printf("[%d]%s\t%s\n",i,p->name,p->phone);
}
printf("gongxianshile%dtiaoshuju\n",addr_book->size);
}
void clearallpersoninfo(addressbook* addr_book){
addr_book->size=0;

}


int main(){
init(&g_address_book);
typedef void (*pfunc_t)(addressbook*);
pfunc_t table[]={
  addpersoninfo,
  delpersoninfo,
  modifypersoninfo,
  findpersoninfo,
  sortpersoninfo,
  printallpersoninfo,
  clearallpersoninfo,
};
while(1){
  int choice=menu();
  if(choice<0||(choice>(int)(sizeof(table)/sizeof (table[0])))){
    printf("nindeshuruyouwu\n");
  }
  if(choice==0){
    printf("goodbye!\n");
    break;
  }
 table[choice-1](&g_address_book); 
}
return 0;
}
