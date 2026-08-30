#include <iostream>
#include <map>

// 3/8
//
// 3/7

int gcd(int a, int b){
  int M, m;
  if(a < b) std::swap(a, b);
  while(a != b){
    M = std::max(a-b, b);
    m = std::min(a-b, b);
    a=M;
    b=m;
  }
  return a;
}

int main() {
  std::cout.precision(10);
  int a = 0, c = 3, na = 2;
  int b = 0, d = 7, nb=5;
  int g = 0;
  while(nb < 1000000){
    a = na;
    b = nb;
    na += c;
    nb += d;
    g = gcd(na, nb);
  }
  std::cout << a << "/" << b << std::endl;
  return 0;
}

