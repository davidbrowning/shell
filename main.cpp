#include "shell.hpp"

#include<string>
#include<signal.h>
#include"color.hpp"



int startShell();
std::vector<std::string> parseCommand(std::string);



int main(){
startShell();
return EXIT_SUCCESS;
}


extern "C" void myHandler(int SignalID);

void myHandler(int SignalID){
 std::cout << "You can't escape that easitly!" << std::endl;
 char workingDirectory[1024];
 getcwd(workingDirectory, sizeof(workingDirectory));
 std::cout << FRED("[ ");
 std::cout << workingDirectory;
 std::cout << FRED(" ]: ");
 std::cout.flush();
}

int startShell(){
shell myshell;
signal(SIGINT, myHandler);
 while(true){
  std::cout << FRED("[ ");
  myshell.pwd();
  std::cout << FRED(" ]: ");
  std::cout.flush();
  std::string cmd = "";
  std::getline(std::cin, cmd); 
  auto parsedCommand = parseCommand(cmd);
  myshell.appendHistory(parsedCommand);
  //myshell.showHistory();
  //going to have to check for pipes here, then for each pipe run execute command
  myshell.executeCommand(parsedCommand);
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
 



