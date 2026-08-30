#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

std::pair<int, int> median(std::pair<int, int> a, std::pair<int, int> b) {
  auto p = std::make_pair(a.first + b.first, a.second + b.second);
  auto g = std::gcd(p.first, p.second);
  return {p.first / g, p.second / g};
}

int gen_seq_len(std::pair<int, int> a, std::pair<int, int> b, int maxD){
  auto m = median(a, b);
  if(m.second > maxD) return 0;
  return 1 + gen_seq_len(a, m,maxD) + gen_seq_len(m, b, maxD);
}

int main() {
  int maxD = 12000;
  std::cout << gen_seq_len({1,2}, {1,3}, 12000)<< std::endl;  

  return 0;
}
