#ifndef SHELL_HPP
#define SHELL_HPP

#include<iomanip>
#include<unistd.h>
#include<sys/wait.h>
#include<chrono>
#include<sstream>
#include<string>
#include<vector>
#include<iostream>
#include<unistd.h>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>


class shell{
 public: 
  shell(){std::cout << "welcome to shell" << std::endl;
  }
  ~shell(){}
  void appendHistory(std::vector<std::string>);
  void showHistory();
  std::vector<std::string> retrieveHistory(int);
  double getPtime();
  void setPtime(double);
  void pwd();
  void changeDirectories(std::vector<std::string>);
  void myHandler(int);
  void executeCommand(std::vector<std::string>);
  void executePipeCommand(std::vector<std::string>);
  void handlePipe(std::vector<std::string>, std::vector<std::string>);
 private:
 std::vector<std::vector<std::string> > history;
 double ptime;
};



#endif
