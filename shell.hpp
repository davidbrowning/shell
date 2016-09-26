#ifndef SHELL_HPP
#define SHELL_HPP


#include<vector>
#include<iostream>
#include<unistd.h>
#include<cstring>

class shell{
 public: 
  shell(){std::cout << "constructor called";}
  ~shell(){}
  void appendHistory(std::vector<std::string>);
  void showHistory();
  std::vector<std::string> retrieveHistory(int);
  double getPtime();
  void setPtime();
  void executeCommand(std::vector<std::string>);
 private:
 std::vector<std::vector<std::string>> history;
  
};

#endif
