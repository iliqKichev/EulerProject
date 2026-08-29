#include <iostream>
#include <vector>

int get_next_num(int n) {
  if (n == 0)
    return 1;
  std::vector<int> fact(10, 1);
  for (int i = 1; i < fact.size(); i++) {
    fact[i] = fact[i - 1] * i;
  }
  int ans = 0;
  while (n > 0) {
    ans += fact[n % 10];
    n /= 10;
  }
  return ans;
}

int chain_length(int num) {
  std::vector<int> chain = {num};

  std::vector<std::vector<int>> repeat = {
      {1},          {2},         {40585}, {145}, {169, 363601, 1454},
      {871, 45361}, {872, 45362}};
  while (true) {
    for (auto const &r : repeat) {
      for (int i = 0; i < r.size(); i++) {
        if (chain.back() == r[i]) {
          return chain.size() + r.size() - 1;
        }
      }
    }
    chain.push_back(get_next_num(chain.back()));
  }
  return 0;
}

int main() {
  int count = 0;
  for (int i = 0; i < 1000000; i++) {
    auto s = chain_length(i);
    if (s == 60)
      count++;
  }
  std::cout << count << std::endl;
}
