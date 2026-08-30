/* x^2 - Dy^2 = 1
 * x^2 = 1 + Dy^2
 *
 * */

#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>
#include <iostream>
#include <optional>
#include <vector>

using boost::multiprecision::cpp_int;

std::vector<int> cont_frac_srqt(int N) {
  int a0 = floor(sqrt(N));
  std::vector<int> seq = {a0};
  if (a0 * a0 == N) {
    return seq;
  }

  int count = 0;
  int m = 0;
  int d = 1;
  while (seq.back() != 2 * a0) {
    count++;
    m = d * seq.back() - m;
    d = (N - m * m) / d;
    seq.push_back(floor(double(a0 + m) / d));
  }

  return seq;
}

std::pair<cpp_int, cpp_int> fraction_from_seq(std::vector<int> const &seq) {
  std::pair<cpp_int, cpp_int> p = {1, seq.back()};
  for (int i = seq.size() - 2; i >= 0; i--) {
    p = {p.second, seq[i] * p.second + p.first};
  }
  return {p.second, p.first};
}

std::optional<std::pair<cpp_int, cpp_int>> solve_diophantine_eq(int N) {
  auto f = cont_frac_srqt(N);
  int fsize = f.size();
  if (fsize == 1) {
    return std::nullopt;
  }
  if (fsize % 2) {
    f.pop_back();
  } else {
    for (int i = 1; i < fsize - 1; i++)
      f.push_back(f[i]);
  }

  return fraction_from_seq(f);
}

int main() {
  int D = 1000;

  cpp_int maxX = -1;
  int maxID = -1;

  for (int i = 1; i <= D; i++) {
    auto s = solve_diophantine_eq(i);
    if (s.has_value()) {
      //    std::cout << s.value().first <<" " << i << " " << s.value().second
      //    << std::endl;
      if (maxX < s.value().first) {
        maxX = s.value().first;
        maxID = i;
      }
    }
  }
  std::cout << maxID << std::endl;

  return 0;
}
