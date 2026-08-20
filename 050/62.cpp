#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>

using boost::multiprecision::cpp_int;

unsigned long long make_key(cpp_int num) {
  std::vector<unsigned long long> digits(10, 0);
  std::string str{num.str()};

  for (auto c : str) {
    digits[c - '0']++;
  }

  unsigned long long s = 0;
  for (auto d : digits) {
    s += d;
    s *= 100;
  }
  return s;
}

int main() {

  std::unordered_map<unsigned int, std::vector<cpp_int>> cubes;
  cpp_int UPPER_BOUND = 10000;
  for (cpp_int a = 1; a < UPPER_BOUND; a++) {
    auto k = make_key(a*a*a);
    cubes[k].push_back(a);
  }
  
  cpp_int minC = UPPER_BOUND;
  for(auto const& [k, v]: cubes){
    if(v.size() == 5){
      for(auto const& n: v){
        minC = boost::multiprecision::min(n, minC);
      }
    }
  }
  std::cout << minC*minC*minC << std::endl;
}
