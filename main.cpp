#include "shell.hpp"
#include<sstream>
#include<string>
#include<cstdlib>


int startShell();
std::vector<std::string> parseCommand(std::string);

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
  auto parsedCommand = parseCommand(cmd);
  myshell.appendHistory(parsedCommand);
  myshell.showHistory();
 }


return 0;
}


std::vector<std::string> parseCommand(std::string s){
   std::vector<std::string> argvVector;
   std::istringstream iss(s);
  do{
   std::string cx;
   iss >> cx;
   argvVector.push_back(cx);
   } while (iss);
  return argvVector;
 }
/* int i = argvVector.size();
 char** argv = new char*[i];
 argv[i] = NULL;
 i--;
 for(i;i>=0;i--){
  argv[i] = new char[5];
  std::string cmd = argvVector.at(i);
  strcpy(argv[i], cmd.c_str());
  std::cout << "argv["<<i<<"]"<<argv[i]<<std::endl;
 }
 std::cout << "made it here" << std::endl;
 return argv;
 }
*/
 



