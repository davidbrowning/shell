#include "shell.hpp"


void shell::appendHistory(std::vector<std::string> c){
 history.push_back(c);

 return;
}

std::vector<std::string> shell::retrieveHistory(int c){
 c = c-1;
 if(history.at(c).empty() == false){
  return history.at(c);
 }
 else {std::vector<std::string> v;
  v.push_back("Invalid Selection");
  return v;
 }
}

void shell::showHistory(){
int i = 1; 
std::cout << "--Command History--" << std::endl;
 for(std::vector<std::string> c : history){
 std::cout << i << ": ";
  for(std::string s : c){
    std::cout << s << " ";
  }
 std::cout << std::endl;
 i++;
 }
return;

}

void help(){
 std::cout << "Shell program. Written by David Browning" << std::endl;
 std::cout << "Built in commands are:" << std::endl;
 std::cout << "\t ptime: shows the time it took to run the last process" << std::endl;
 std::cout << "\t history: shows all commands entered during this instance of the shell" << std::endl;
 std::cout << "\t ^ <number>: displays then runs the <number>th command in history" << std::endl;
 std::cout << "\t exit: exits the shell" << std::endl << std::endl;
 std::cout << "Shell will also attempt to run any commands located by your PATH variable using the execvp function" << std::endl;
return;
}

void shell::setPtime(double t){
 ptime += t;
 return;
}

double shell::getPtime(){
 std::cout << "Total time executing child processes: " << std::setprecision(5) <<ptime << std::endl;
 return ptime;
}

void shell::pwd(){
 char workingDirectory[1024];
 getcwd(workingDirectory, sizeof(workingDirectory));
 std::cout << workingDirectory;
}

void shell::changeDirectories(std::vector<std::string> cmd){
 //const char *pa = "..";
 //chdir(pa);

   char dir[10];
 if(cmd.at(1).empty() == false){
   strcpy(dir,cmd.at(1).c_str());
  }
 const char *goingHere = dir;
 chdir(goingHere);
}

void shell::executeCommand(std::vector<std::string> cmd){
 std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
 //execute function
 if(cmd.at(0) == "exit" || cmd.at(0) == "EXIT"){std::exit(0);}
 else if(cmd.at(0) == "help" || cmd.at(0) == "HELP"){help();}
 else if(cmd.at(0) == "history" || cmd.at(0) == "HISTORY"){showHistory();}
 else if(cmd.at(0) == "ptime" || cmd.at(0) == "PTIME"){getPtime();}
 else if(cmd.at(0) == "pwd" || cmd.at(0) == "PWD"){pwd();}
 else if(cmd.at(0) == "cd" || cmd.at(0) == "CD"){changeDirectories(cmd);}
 else if(cmd.at(0) == "^"){
   try {int index = std::stoi (cmd.at(1));
    auto cmdx = retrieveHistory(index);
    executeCommand(cmdx);} 
    catch (std::exception &e){
    std::cout << "Invalid Argument!"<< std::endl;
    }
   }
 else if(cmd.at(0).empty() == false){
//  std::cout << "cmd.at(0): " << cmd.at(0) << std::endl;
//  std::cout << "cmd.size(): " << cmd.size() << std::endl;
  char** argv = new char*[(cmd.size())];
  int i = 0;
  for(i; i < cmd.size()-1; i++){
   if(cmd.at(i).empty() == false){
//    std::cout << "cmd.at(" << i << ")" << cmd.at(i) << std::endl;
    argv[i] = new char[5];
    strcpy(argv[i],cmd.at(i).c_str());
   }
  }
 i = (cmd.size()-1);
 argv[i] = NULL;
 if(fork()){
  wait(NULL);
  //execvp(argv[0], argv);
 }
 else{
  if(execvp(argv[0], argv) == -1){
   std::cout << "Something went wrong.(execvp returned -1) \n Possible causes:\n \t 1) command not in path variable \n \t 2) Invalid command/arguments " << std::endl;
   std::cout << "For help, type \"help\" \n exiting child process..." << std::endl;
   std::vector<std::string> v;
   v.push_back("exit");
   executeCommand(v);
  }
 }

 }
 
 //get end time
 std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();

 //total = end minus start
 std::chrono::duration<double> totalTime = end - start;
 setPtime(totalTime.count());
}


