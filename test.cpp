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
auto t = timer(test);
std::cout << t.count() << std::endl;
auto p = timer(8, params);
std::cout << p.count() << std::endl;
return 0;
}
