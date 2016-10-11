#include "shell.hpp"

#include<string>
#include<signal.h>


extern "C" void MyHandler(int SignalID);

int startShell();
std::vector<std::string> parseCommand(std::string);



int main(){
	signal(SIGINT, MyHandler);
startShell();
return EXIT_SUCCESS;
}

void MyHandler(int SignalID){
	std::cout << "You can't escape that easily!" <<  std::endl << "[cmd]:";
	std::cout.flush();
	exit(0);
}

int startShell(){
shell myshell;
 while(true){
  std::cout << "[cmd]:";
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
 



