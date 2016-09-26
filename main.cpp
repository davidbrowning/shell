#include "shell.hpp"
#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include<cstdlib>


int startShell();


int main(){

startShell();
return EXIT_SUCCESS;

}

int startShell(){
shell myshell;
 while(true){
  std::cout << "[cmd]:";
  std::string cmd = "";
  std::getline(std::cin, cmd);
  std::cout << cmd << std::endl;
  

 }


return 0;
}


