all:hehe haha
hehe:p2psevert.cpp
	g++ -std=c++11 -g $^ -lpthread -lboost_filesystem -lboost_system  -o $@
haha:p2pClient.cpp
	g++ -std=c++11 -g   $^ -lpthread -lboost_filesystem -lboost_system -o $@ 
