#include "shell.hpp"

#include<string>
#include<signal.h>
#include<memory>
#include"color.hpp"
#include"shell.cpp"



int startShell();
std::vector<std::string> parseCommand(std::string);
int findPipe(std::vector<std::string>);

int main(){
startShell();
return EXIT_SUCCESS;
}


extern "C" void myHandler(int SignalID);

void myHandler(int SignalID){
 std::cout << "You can't escape that easily!" << std::endl;
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
  int p = findPipe(parsedCommand);
  //myshell.showHistory();
  //going to have to check for pipes here, then for each pipe run execute command
  if(p == -1){myshell.executeCommand(parsedCommand);}
  else{
   std::vector<std::string> cmd1;
   std::vector<std::string> cmd2;
   std::cout << p << std::endl;
   for(int i = 0; i < parsedCommand.size() - 1; i++){
    if(i < p){cmd1.push_back(parsedCommand.at(i));}
    else if(i > p){cmd2.push_back(parsedCommand.at(i));}
   }
   myshell.handlePipe(cmd1, cmd2);
  }
 }


return 0;
}

int findPipe(std::vector<std::string> fullcmd){
 int i = 0;
 for(i; i < fullcmd.size(); i++){
  if(fullcmd.at(i) == "|"){
   return i;
  }
 }
 return -1;
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
 


