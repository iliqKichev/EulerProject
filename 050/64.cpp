/** n = sqrt(N)
 *  a0 -> biggest square less than sqrt(N)
 *  a1 -> 
 *
 *
 *
 */

#include <cmath>
#include <iostream>

int gen_seq(double N) {
  double n = sqrt(N);
  int a0 = floor(n);
  if (a0 * a0 == N) {
    return 0;
  }
 
  int count = 0;
  int m = 0;
  int d = 1;
  int a = a0;
  while (a != 2 * a0) {
    count++;
    m = d*a - m;
    d = (N-m*m)/d; 
    a = floor(double(a0+m)/d);
  }

  return count;
}

int main() {

  int count_odd = 0;
  for (int i = 1; i <= 10000; i++) {
    int s = gen_seq(i);
    count_odd += s % 2;
  }

  std::cout << count_odd << std::endl;

  return 0;
}
