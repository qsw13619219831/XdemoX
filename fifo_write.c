/*命名管道的基本使用
 * int mkfifo(const char*pathname,mode_t mode)'
 *       pathname:管道文件名
 *       'mode:创建权限 
 *       返回值:成功0,失败-1
 * '
 *
 * */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<string.h>
#include<fcntl.h>
int main(){
      char*file="./test.fifo";
      umask(0);
      int ret=mkfifo(file,0064);
      if(ret<0){
        if(errno!=EEXIST){
          perror("mkdido error");
          return -1;
        }
    }
      int fd=open(file,O_WRONLY);
      if(fd<0){
        perror("open error");
        return -1;
      }
        printf("open success!!\n");
        while(1){
      char buf[1024]={0};
      scanf("%s",buf);
      write(fd,buf,strlen(buf));

        }
        close(fd);
return 0;


}
