#include <iostream>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;
int main() {

  cpp_int s = 1020304050607080900;
  cpp_int a = sqrt(s);
  cpp_int p = 1929394959697989990;
  cpp_int b = sqrt(p);
  std::cout << a << " " << b << std::endl;

  for (cpp_int i = a; i <= b; i++) {
    cpp_int sq = i * i;
    // std::cout << sq << std::endl;
    std::string digits = sq.str();
    bool is_the_number = true;
    for (int j = 0; j < digits.size(); j += 2) {
      if (digits[j] - '0' != (j/2+1)%10) {
        is_the_number = false;
        break;
      }
    }
    if (is_the_number) {
      std::cout << i << " " << sq << std::endl;
    }
  }

  return 0;
}
