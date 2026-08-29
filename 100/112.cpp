#include <cmath>
#include <iostream>
#include <vector>

bool is_decr(int n) {
  int pd = -1;
  while (pd <= n % 10) {
    pd = n % 10;
    n /= 10;
  }
  return n == 0;
}

bool is_incr(int n) {
  int pd = 10;
  while (pd >= n % 10 && n > 0) {
    pd = n % 10;
    n /= 10;
  }
  return n == 0;
}

bool is_bouncy(int num){
  return !(is_decr(num) || is_incr(num));
}
int main() {
  int ub = 10000000;
  int num_bouncy = 0;
  
  for(int i = 100; i < ub;i++){
    num_bouncy += is_bouncy(i); 
    if (fabs(.99 - double(num_bouncy)/i) <= 1e-20){
      std::cout << i << std::endl;
    }
  }
  return 0;
}
