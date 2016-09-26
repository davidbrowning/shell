#include<chrono>
#include<cmath>
#include<functional>

//This file introduces the timeAFunction function. 
//It accepts a function with no arguments as a parameter.
//to add arguments, simply insert them into timeAFunction, and
//then into t();
//For Example: 
//std::chrono::duration<double> timeAFunction(int a, double b,T t){
//t(a, b);
//on the appropriate lines


//since it returns a duration<double> the easiest way to stream this is to use
//the .count() method. 
//For Example (in a different source file): 
//auto funcTime = timer_no_args(function);
//std::cout << funcTime.count() << std::endl;


template<typename T>
std::chrono::duration<double> timer_no_args(T t){
//get starting time
std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
//execute function
t();

//get end time
std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();

//total = end minus start
std::chrono::duration<double> totalTime = end - start;

//return total
return totalTime;
}



template<typename T, typename arg1>
std::chrono::duration<double> timer_one_args(arg1 a1,T t){
//get starting time
std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
//execute function
t(a1);

//get end time
std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();

//total = end minus start
std::chrono::duration<double> totalTime = end - start;

//return total
return totalTime;
}
