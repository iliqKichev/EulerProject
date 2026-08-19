#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/rational.hpp>
#include <iostream>
#include <limits>
#include <string>

using boost::multiprecision::cpp_bin_float_50;

const int ACC = 50;

int floor(cpp_bin_float_50 n) { return static_cast<int>(n); }

cpp_bin_float_50 abs(cpp_bin_float_50 n) {
  if (n > 0)
    return n;
  return -n;
}

cpp_bin_float_50 gen_num(cpp_bin_float_50 theta) {
  cpp_bin_float_50 b = theta;
  std::string s = "2.";
  for (int i = 0; i < ACC; i++) {
    b = floor(b) * (b - floor(b) + 1);
    s += std::to_string(floor(b));
  }
  return boost::lexical_cast<cpp_bin_float_50>(s);
}

cpp_bin_float_50 find_num(cpp_bin_float_50 beg, cpp_bin_float_50 end,
                          int n = 1) {
  cpp_bin_float_50 mid = beg + (end - beg) / 2;
  cpp_bin_float_50 theta = gen_num(mid);
  if (abs(mid - theta) <= 1e-50) {
    return mid;
  }
  if (mid > theta) {
    return find_num(beg, mid);
  }
  return find_num(mid, end);
}

int main() {
  cpp_bin_float_50 theta = 2.956938891377988;
  std::streamsize precision = std::numeric_limits<cpp_bin_float_50>::digits10;

  std::cout.precision(precision);
  std::cout << theta << std::endl;
  std::cout << gen_num(theta) << std::endl;
  cpp_bin_float_50 n = find_num(2.0, 3.0);
  std::cout << n << std::endl;
  std::cout << gen_num(n) << std::endl;

  return 0;
}
// 2.2235610193135541061731771952804868081407232136055
