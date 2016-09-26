#include<vector>
#include<iostream>
#include<unistd.h>
#include<cstring>

class shell{
 public: 
  shell(){std::cout << "constructor called";}
  ~shell(){}
  appendHistory(char**);
  retrieveHistory();
  getPtime();
  setPtime();
  executeCommand(char**);
 private:
  vector<char**> history;
  
};
