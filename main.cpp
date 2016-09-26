#include "shell.hpp"
#include<sstream>
#include<string>
#include<cstdlib>


int startShell();
char** parseCommand(std::string);

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
  auto parsedCommand = parseCommand(cmd); 

 }


return 0;
}

char** parseCommand(std::string s){ 
 if(s == "" || s == " "){
  return NULL;
 }
 else{
   std::vector<std::string> argvVector;
   std::istringstream iss(s);
  do{
   std::string cx;
   iss >> cx;
   argvVector.push_back(cx);
   } while (iss);
 int i = argvVector.size();
 char** argv = new char*[i];
 argv[i] = NULL;
 i--;
 for(i;i>=0;i--){
  argv[i] = new char[10];
  std::string cmd = argvVector.at(i);
  strcpy(argv[i], cmd.c_str());
  std::cout << "argv["<<i<<"]"<<argv[i]<<std::endl;
 }
 return argv;
 }
return NULL;
 
}


