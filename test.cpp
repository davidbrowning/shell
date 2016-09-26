#include<iostream>
#include"timer.cpp"

void test(){
std::cout << "it worked!!" << std::endl;
return;
}

void params(int a){
 std::cout << a << std::endl;
}

int main(){
auto t = timer_no_args(test);
std::cout << t.count() << std::endl;
auto p = timer_one_args(8, params);
std::cout << p.count() << std::endl;
return 0;
}
