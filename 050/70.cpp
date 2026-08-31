#include <iostream>
#include <vector>

int euler_phi(int n, double min_ratio, std::vector<int> const &primes) {
  int phi = n, red = n;
  for (auto p : primes) {
    if (red % p == 0) {
      phi -= phi / p;

      while (red % p == 0)
        red /= p;

      if (phi * min_ratio < n)
        return phi;
    }
  }
  if (phi > 1)
    return phi - phi / red;
  else
    return phi;
}

std::vector<int> get_digits_of(int n) {
  std::vector<int> digits(10, 0);
  while (n > 0) {
    digits[n % 10]++;
    n /= 10;
  }
  return digits;
}

bool is_perm(int a, int b) {
  auto da = get_digits_of(a);
  auto db = get_digits_of(b);
  for (int i = 0; i < 10; i++) {
    if (da[i] != db[i])
      return false;
  }
  return true;
}

int main() {
  long long maxN = 10000000;
  std::vector<int> primes = {2};
  for (int i = 3; primes.back()*primes.back() <= maxN; i += 2) {
    bool is_prime = true;
    for (auto p : primes) {
      if (p * p > i)
        break;
      if (i % p == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime) {
      primes.push_back(i);
    }
  }

  double min_ratio = maxN;
  int min_id = 0;
  for (int i = 2; i < maxN; i++) {
    int phi = euler_phi(i, min_ratio, primes);
    double q = i / double(phi);
    if (q < min_ratio) {
      if (is_perm(i, phi)) {
        min_ratio = q;
        min_id = i;
      }
    }
  }
  std::cout << min_id << std::endl;
  std::cout << euler_phi(min_id, 10,  primes) << std::endl;
  std::cout << (min_id / double(euler_phi(min_id, 10, primes))) << std::endl;
  return 0;
}
