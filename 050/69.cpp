#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
  std::vector<int> primes;
  for (int i = 2; i <= 100; i++) {
    bool is_prime = true;
    for (auto k : primes) {
      if (i % k == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime)
      primes.emplace_back(i);
  }

  int pid = 0, num = 1;
  while (num < 1000000) {
    num *= primes[pid];
    pid++;
  }
  num = std::max(num / primes[pid], num / primes[pid - 1]);
  std::cout << num << std::endl;
  return 0;
}
