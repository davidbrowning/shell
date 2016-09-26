#include "shell.hpp"

void shell::appendHistory(std::vector<std::string> c){
 history.push_back(c);

 return;
}

std::vector<std::string> shell::retrieveHistory(int c){
 if(history.at(c).empty() == false){
  return history.at(c);
 }
 else {std::vector<std::string> v = {"Invalid Command"};
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


