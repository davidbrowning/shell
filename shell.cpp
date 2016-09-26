#include "shell.hpp"

void shell::appendHistory(std::vector<std::string> c){
 history.push_back(c);

 return;
}

std::vector<std::string> shell::retrieveHistory(int c){
 if(history.at(c).empty() == false){
  return history.at(c);
 }
 else {std::vector<std::string> v;
  v.push_back("Invalid Selection");
  return v;
 }
}

void shell::showHistory(){
 for(std::vector<std::string> c : history){
  for(std::string s : c){
    std::cout << s << " ";
  }
 std::cout << std::endl;
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
 std::cout << "Total time executing child processes: " << ptime << std::endl;
 return ptime;
}

void shell::executeCommand(std::vector<std::string> cmd){

 std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
 //execute function
 if(cmd.at(0) == "exit" || cmd.at(0) == "EXIT"){std::exit(0);}
 else if(cmd.at(0) == "help" || cmd.at(0) == "HELP"){help();}
 else if(cmd.at(0) == "history" || cmd.at(0) == "HISTORY"){showHistory();}
 else if(cmd.at(0) == "ptime" || cmd.at(0) == "PTIME"){getPtime();}
 else if(cmd.at(0) == "^"){
   try {int index = std::stoi (cmd.at(1));
    auto cmdx = retrieveHistory(index);
    executeCommand(cmdx);} 
    catch (std::exception &e){
    std::cout << "Invalid Argument!"<< std::endl;
    }
   }
 else if(cmd.at(0).empty() == false){
  //std::cout << "not empty!" << std::endl;
  int j = cmd.size();
  char** argv = new char*[j];
 // std::cout << "argv created" << std::endl;
  argv[j] = NULL;
  //std::cout << "argv last element set to null" << std::endl;
  for (int i = cmd.size() - 1; i >= 0; i--){
   argv[i] = new char[5];
   //std::cout << "argv["<<i<<"] initialized" << std::endl;
   std::string cm = cmd.at(i);
   //std::cout << "cmd.at successfully copied" << cm << std::endl;
   strcpy(argv[i],cm.c_str());
   std::cout << "argv[0]" << argv[0] << std::endl;
   //execvp(argv[0], argv);
  }
 }
 
 //get end time
 std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();

 //total = end minus start
 std::chrono::duration<double> totalTime = end - start;
 setPtime(totalTime.count());
}


