#include <cmath>
#include <iostream>
#include <unordered_set>
#include <vector>

int main() {
  int MAX_NUM = 50000000;
  int sq = std::sqrt(MAX_NUM);
  int trd = std::powf(MAX_NUM, 1.0 / 3);
  int tetr = std::powf(MAX_NUM, 0.25);

  std::vector<int> primes = {2};
  for (int i = 3; i <= sq; i+=2) {
    bool flag = true;
    for (int p : primes) {
      if (i % p == 0) {
        flag = false;
        break;
      }
    }
    if (flag)
      primes.push_back(i);
  }
  
  std::unordered_set<int> nums;

  for (int i : primes) {
    for (int j : primes) {
      if (j > trd)
        break;
      for (int k : primes) {
        if (k > tetr)
          break;
        int n = i * i + j * j * j + k * k * k * k;
        if (n < MAX_NUM){
          nums.insert(n);
        }
      }
    }
  }

  std::cout << nums.size() << std::endl;

  return 0;
}
