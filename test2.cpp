// g++ test.cpp --std=c++11
#include <functional>

double Combiner(double a, double b, std::function<double (double,double)> func){
  return func(a,b);
}

double Add(double a, double b){
  return a+b;
}

double Mult(double a, double b){
  return a*b;
}

int main(){
  Combiner(12,13,Add);
  Combiner(12,13,Mult);
}
