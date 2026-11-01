#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>

using namespace boost::multiprecision;

int main() {
  std::vector<cpp_int> P(1 << 18, 0);
  P[0] = 1;
  int N = 60000;

  for (int n = 1; n <= N; n++) {
    for (int k = n; k <= N; k++) {
      P[k] += P[k - n];
    }
  }


  for (int i = 1; i <= N; i++) {
    if (P[i] % 1000000 == 0) {
      std::cout << i << std::endl;
      std::cout << P[i] << std::endl;
      return 0;
    }
  }

  return 0;
}
