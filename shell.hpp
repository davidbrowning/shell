#ifndef SHELL_HPP
#define SHELL_HPP

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
  shell(){std::cout << "welcome to shell" << std::endl;}
  ~shell(){}
  void appendHistory(std::vector<std::string>);
  void showHistory();
  std::vector<std::string> retrieveHistory(int);
  double getPtime();
  void setPtime(double);
  void executeCommand(std::vector<std::string>);
 private:
 std::vector<std::vector<std::string> > history;
 double ptime;
};

#endif
