#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>

using boost::multiprecision::cpp_int;

std::pair<cpp_int, cpp_int> fraction_from_seq(std::vector<cpp_int> const &seq) {
  std::pair<cpp_int, cpp_int> p = {1, seq.back()};
  for (int i = seq.size() - 2; i >= 0; i--) {
    p = {p.second, seq[i] * p.second + p.first};
  }
  return {p.second, p.first};
}

int sum_of_digits(cpp_int n) {
  int s = 0;
  for (char c : n.str()) {
    s += c - '0';
  }
  return s;
}

int main() {
 int n_term = 100;
  std::vector<cpp_int> e = {2};
  e.reserve(128);
  for (int i = 0; i < n_term / 3; i++) {
    e.push_back(1);
    e.push_back(2 * (i + 1));
    e.push_back(1);
  }
  // e.push_back(1);
  auto p = fraction_from_seq(e);
  std::cout << p.first << " " << p.second << std::endl;
  std::cout << sum_of_digits(p.first) << std::endl;
  return 0;
}
