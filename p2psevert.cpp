#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include<stdio.h>
#include<string>
#include<unistd.h>
#include<pthread.h>
#include<ostream>
#include<boost/filesystem.hpp>
#include"httplib.h"
#define SHAR_DIR "HEHE"
using std::cout;
using std::endl;
using namespace httplib;
namespace bf=boost::filesystem;
class P2Pservet
{
  public:
    P2Pservet(){ 
    }
    void start(){
      
      _srv.Get("/hostpair",pairhandle);
      _srv.Get("/HEHE",Listhandle);
      _srv.Get("/HEHE/(.*)",Downhandle);
      _srv.listen("0.0.0.0",9002);
    }
    static void  pairhandle(const Request& req, Response& res){
      res.status=200;
      cout<<"new client connected"<<endl;
    }

    static void  Listhandle(const Request& req, Response& res){
      if(bf::exists(SHAR_DIR)){
        cout<<"have new client read list"<<endl;
      }
      else{
        bf::create_directory(SHAR_DIR);
        cout<<"dosent have dir, created!and new client read list"<<endl;
      }
      std::vector<std::string> dirList;
      bf::recursive_directory_iterator beg_it(SHAR_DIR);
      bf::recursive_directory_iterator end_it;
      for(;beg_it!=end_it;beg_it++){
        if(bf::is_directory(*beg_it)){
          continue;
        }
        else{
          std::string names =  beg_it->path().string();
          dirList.push_back(names);
          res.body += names+'\n';
        }
      }
      res.status=200;
    }


    static void  Downhandle(const Request& req, Response& res){
    bf::path path(req.path.c_str());
    std::string paths=path.filename().c_str();
    std::string dir="./";
    std::string shar=SHAR_DIR;
    dir.append(shar);
    dir.push_back('/');
    dir.append(paths);
    bf::path localpath(dir.c_str());
    std::string body;
    FILE *fd=fopen(dir.c_str(),"r");
    if (fd==NULL){
    cout<<"open file fail"<<endl;
    res.status=209;
    body="open file fail";
    res.body=body;
    return ;
    }
    char*buf=(char*)malloc(bf::file_size(localpath));
    fread(buf,1,bf::file_size(localpath),fd);
    res.body=buf;
    res.status=200;
    cout<<"somebody downlaod doc!"<<endl;
    fclose(fd);
    free(buf);
    }


  private:
    Server _srv;
};
int main(){
P2Pservet s;
s.start();

}

