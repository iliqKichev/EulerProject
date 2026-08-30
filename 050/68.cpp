#include <algorithm>
#include <iostream>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <vector>

std::optional<std::vector<short>> is_pentagon(std::vector<short> &s) {
  // 0 1 2 // 3 2 4 // 6 4 5 //
  // 4 3 2 // 6 2 1 // 3 1 5 //
  std::vector<std::vector<short>> sumIDs = {
      {0, 1, 2}, {3, 2, 4}, {4, 5, 6}, {6, 7, 8}, {9, 8, 1}};
  std::vector<short> sums(sumIDs.size(), 0);
  for (short i = 0; i < sums.size(); i++) {
    for (short j : sumIDs[i]) {
      sums[i] += s[j];
    }
  }
  for (short a : sums) {
    if (a != sums[0]) {
      return std::nullopt;
    }
  }
  std::vector<short> ansIDs = {0, 1, 2, 3, 2, 4, 5, 4, 6, 7, 6, 8, 9, 8, 1};
  std::vector<std::vector<short>> ans;
  for (short i = 0; i < 5; i++) {
    ans.push_back({});
    for (short j = 0; j < ansIDs.size(); j++) {
      ans.back().push_back(s[ansIDs[(j + i * 3) % ansIDs.size()]]);
    }
  }
  auto minS = ans[0];
  for (auto a : ans)
    minS = std::min(a, minS);

  return minS;
}

int main() {
  std::vector<short> s(10, 0);
  for (int i = 0; i < s.size(); i++)
    s[i] = i + 1;

  std::set<std::string> res;

  bool is_not_done = true;
  while (is_not_done) {
    if (auto ans = is_pentagon(s); ans.has_value()) {
      std::stringstream ss;
      for (auto a : ans.value())
        ss << a;
      res.insert(ss.str());
    }

    is_not_done = std::next_permutation(s.begin(), s.end());
  }
 for(auto r: res)
    std::cout << r << std::endl;
  return 0;
}
