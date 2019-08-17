#include<iostream>
#include<sys/types.h>
#include<ifaddrs.h>
#include<thread>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<stdio.h>
#include<string>
#include<boost/thread.hpp>
#include<unistd.h>
#include<pthread.h>
#include<boost/bind.hpp>
#include<ostream>
#include<boost/filesystem.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include"httplib.h"
#define SHAR_DIR "HEHE"
using std::cout;  
using std::cin;
using std::endl;                            
using namespace httplib;
namespace bf=boost::filesystem;   
#define DOWNLOAD_DIR "download"
#define RANGE_SIZE (10 << 20)
class P2pClient
{
  private:
    std::string _filename;
    std::string _wantip; 
    std::vector<std::string> _host_list;
    std::vector<std::string> _file_list;
  private:
    bool GetHostList(std::vector<std::string> &list){
      struct ifaddrs *addr=NULL;
      struct ifaddrs *ifaddr=NULL;
      int ret= getifaddrs(&ifaddr);
      if(ret < 0){
        cout<<"getifaddrs erro!"<<endl;
        return false;
      }
      for(addr=ifaddr;addr!=NULL;addr=addr->ifa_next){
        if(addr->ifa_addr==NULL){
          continue;
        }
        std::string temip;
        struct sockaddr_in *tem=NULL;
        struct sockaddr_in *tems=NULL;
        tem=(struct sockaddr_in*)addr->ifa_addr;
        tems=(struct sockaddr_in*)addr->ifa_netmask; 
        if(tem->sin_family != AF_INET)
          continue;

        temip=inet_ntoa((*tem).sin_addr);
        if(temip=="127.0.0.1")
          continue;  

        uint32_t host= ntohl(~(tems->sin_addr.s_addr));
        uint32_t net= ntohl(tems->sin_addr.s_addr & tem->sin_addr.s_addr);
        uint32_t i;
        for(i=2;i < host;i++){
          struct sockaddr_in help;
          help.sin_addr.s_addr=htonl(net+i);
          list.push_back(inet_ntoa(help.sin_addr));

        }
      }

      return true;
    }
    int64_t GetFileSize(int file_id);

  public:
    void doface(){
      while(true){
        cout<<"==============================="<<endl<<endl; 
        cout<<"please choice what you want"<<endl;
        cout<<"0.quit this app"<<endl; 
        cout<<"1.show online host"<<endl<<endl;
        cout<<"==============================="<<endl;
        int choice=0;
        cin>>choice;
        if(choice==0){
          break;
        }
        else if(choice==1){
          if(ShowNearByHost()){
            cout<<"get online host sucess"<<endl;
          }
          else{
            cout<<"get online hosy fail"<<endl;
          }
        }
        else{
          cout<<"its not a good choice!"<<endl;
          continue;
        }

      }
    }
    void PairNearbyHost(const std::string ip){
      Client _client(ip.c_str(),9002);
      std::shared_ptr<Response> rsp;
      rsp=_client.Get("/hostpair");
      if(rsp&&rsp->status==200){
        _host_list.push_back(ip);
      }
      return ;
    }

    bool ShowNearByHost(){
      cout<<"==============================="<<endl;
      std::vector<std::string> arr;
      GetHostList(arr);
      std::vector<std::thread>tasklist ;
      for(size_t i=0;i < 1;i++){
      //std::thread a(&P2pClient::PairNearbyHost,this,arr[i]);
        std::thread a(&P2pClient::PairNearbyHost,this,"192.168.126.132");
      
        tasklist.push_back(std::move(a));
      }
      for(size_t i=0;i < tasklist.size();i++){
        tasklist[i].join();
      }
      for(size_t i=0;i < _host_list.size();i++){
        cout<<i<<"."<<_host_list[i]<<endl;
      }
      cout<<"==============================="<<endl;
      cout<<"choice what host you want!"<<endl;
      size_t i=0;
      cin>>i;
      if(i>=_host_list.size()){
        return false;
      }
      _wantip=_host_list[i];
      GetShareList(_host_list[i]);
      return true;
    }
    bool GetShareList(std::string ip){
      Client client(ip.c_str(),9002);
      auto rsp=client.Get("/HEHE");
      if(rsp&&rsp->status==200){
        size_t last=0;
        for(size_t i=0;i < rsp->body.size();i++){
          if(rsp->body[i]=='\n'){
            std::string tem=rsp->body.substr(last,i-last);
            last=i+1;
            _file_list.push_back(tem);
          }
        }
        _file_list.push_back(rsp->body.substr(last));
        ShowShareList();
        return true;
      }
      cout<<"get file list fail!"<<endl;
      return false;
    }
    void ShowShareList(){
      cout<<"==============================="<<endl;
      for(size_t i=0;i < _file_list.size();i++ ){
        cout<<i<<"."<<_file_list[i]<<endl;
      } 
      cout<<"==============================="<<endl;
      cout<<"what file you want get?"<<endl;
      size_t num=0;
      cin>>num;
      if(num > _file_list.size()){
        cout<<"dont have this nums file"<<endl;
        return ;
      }
      _filename=_file_list[num];
      DownLoadFile();
    }
    bool DownLoadFile(){
      Client client(_wantip.c_str(),9002);
      std::string lujing="/";
      lujing+=_filename;
      auto rsp= client.Get(lujing.c_str());
      if(rsp&&rsp->status==200){
        if(bf::exists(DOWNLOAD_DIR)){
          cout<<"ready to down"<<endl;
        }
        else{ 
          bf::create_directory(DOWNLOAD_DIR);
          cout<<"doesent have downdir ,create!"<<endl; 
        } 
       size_t pos= _filename.find('/');
       std::string rfilename=_filename.substr(pos+1);
       std::string openpath(DOWNLOAD_DIR);
      openpath+="/";
      openpath+=rfilename;
      FILE*fd=fopen(openpath.c_str(),"w+");
      if(fd==NULL){
        cout<<"create file fail"<<endl;
        return false;
      }
      fwrite(rsp->body.c_str(),1,rsp->body.size(),fd);
      cout<<"file down ok!"<<endl;
      return true;
      }
      return false;
    }
};
    int main(){ 
    
      while(1){
      P2pClient p;
        p.doface();
    }
    }
