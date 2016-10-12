#include "shell.hpp"

#include<string>
#include<signal.h>


extern "C" void MyHandler(int SignalID);

int startShell();
std::vector<std::string> parseCommand(std::string);
int detectPipe(std::vector<std::string> &pc);
void pipeCommands(std::vector<std::string>, std::vector<std::string>, shell &s);


int main(){
	signal(SIGINT, MyHandler);
startShell();
return EXIT_SUCCESS;
}

void MyHandler(int SignalID){
	std::cout << "You can't escape that easily!" <<  std::endl << "[cmd]:";
	std::cout.flush();
}

int startShell(){
shell myshell;
 while(true){
  std::cout << "[cmd]:";
  std::string cmd = "";
  std::getline(std::cin, cmd); 
  auto parsedCommand = parseCommand(cmd);  
  myshell.appendHistory(parsedCommand);
  int pipeAt = detectPipe(parsedCommand);
  if(pipeAt != -1){
	std::vector<std::string> pc1;
	std::vector<std::string> pc2;
	  //do stuff to handle pipe
	  for(int i = 0; i < parsedCommand.size(); ++i){
		if(i < pipeAt){
			pc1.push_back(parsedCommand.at(i));
		}
		else if(i > pipeAt){	
			pc2.push_back(parsedCommand.at(i));
		}
	  }
	  pipeCommands(pc1, pc2, myshell);
  }
  else{
  //myshell.showHistory();
  //going to have to check for pipes here, then for each pipe run execute command
  myshell.executeCommand(parsedCommand,false);
  }
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

int detectPipe(std::vector<std::string> &parsedCmd){
 	for(int i = 0; i < parsedCmd.size(); ++i){
		if(parsedCmd.at(i) == "|"){
			std::cout << "found a pipe!" << std::endl;
			return i;
		}
	}
	return -1;
}

void pipeCommands(std::vector<std::string> one, std::vector<std::string> two, shell &s){
	const int PIPE_COUNT = 2;
	const int PIPE_READ_END = 0;
	const int PIPE_WRITE_END = 1;
	const int STDIN = 0;
	const int STDOUT = 1;

	int pids[PIPE_COUNT];
	pipe(pids);

	int myOut = dup(STDOUT);
	int myIn = dup(STDIN);

	pid_t pid = fork();
	if(pid == 0){
		dup2(pids[PIPE_WRITE_END], STDOUT);
		s.executeCommand(one, true);
	}
	pid_t pid2 = fork();
	if(pid2 == 0){
		dup2(pids[PIPE_READ_END], STDIN);
		close(pids[PIPE_WRITE_END]);
		s.executeCommand(two, true);
	}
	int status;
	waitpid(pid, &status, 0);

	close(pids[PIPE_WRITE_END]);
	close(pids[PIPE_READ_END]);

	waitpid(pid2, &status, 0);

	dup2(myOut, STDOUT);
	dup2(myIn, STDIN);


	/*const int PIPE_COUNT = 2;
	const int PIPE_READ_END = 0;
	const int PIPE_WRITE_END = 1;

	const int STDIN = 0;
	const int STDOUT = 1;
	int pids[PIPE_COUNT]; //pids is an array of size 2?;
	pipe(pids); // Create a new pipe, pass in 2 as a parameter

	int savedStdout = dup(STDOUT); //pass in 1 to this dup function, store the result in savedStdout
	int savedStdin = dup(STDIN); //pass in 0 to this dup function, store the result in savedStdin

	//
	// First child will output the source code to this program to the pipe
	pid_t pid = fork();//this thing of type pid_t gets fork();
	if (pid == 0) //If it is 0, 
	{
		dup2(pids[PIPE_WRITE_END], STDOUT); //No idea what dup2 does.

		s.executeCommand(one);
	}

	//
	// Second child will 'more' whatever input comes down over the pipe
	pid_t pid2 = fork();//this other thing of pid_t gets fork();
	if (pid2 == 0) //If it is 0
	{
		dup2(pids[PIPE_READ_END], STDIN); // still not quite sure what dup2 does.
		//
		// This is key, in order to terminate the input from the pipe
		// have to close off the write end, otherwise the 'more' command
		// will continue to wait for additional data.
		close(pids[PIPE_WRITE_END]); //close the pipe. 

		s.executeCommand(two);
	}

	//
	// Wait for the first child to finish
	int status;
	waitpid(pid, &status, 0);

	//
	// Fully close down the pipe, and yes, for whatever reason, it requires
	// the parent process to close both ends, even though the second child
	// already closed the write end...not sure I fully understand this.
	close(pids[PIPE_WRITE_END]);
	close(pids[PIPE_READ_END]);

	waitpid(pid2, &status, 0);

	//
	// Restore standard out and in, so our program will be back to normal when complete
	dup2(savedStdout, STDOUT);
	dup2(savedStdin, STDIN);

	std::cout << "Enter something: ";
	std::string input;
	std::getline(std::cin, input);
	std::cout << "You entered..." << input << std::endl;
*/
	return;
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
 



