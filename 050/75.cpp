#include <iostream>
#include <set>
#include <unordered_map>

// See https://en.wikipedia.org/wiki/Pythagorean_triple#A_variant

int main() {
  int num = 0, per = 1500000;
  std::unordered_map<int, std::set<int>> count;

  for (int m = 1; m * m < per; m++) {
    for (int n = 1; n < m; n++) {
      if (m % n || n == 1) {
        if ((m % 2) * (n % 2) == 0) {
          int p = 2 * m * (m + n);
          for (int k = 1; k * p <= per; k++) {
            count[k * p].insert(std::min(k * (m * m - n * n), k * 2 * m * n));
          }
        }
      }
    }
  }
  for (auto &[k, v] : count) {
    num += v.size() == 1;
  }
  std::cout << num << std::endl;
  return 0;
}
