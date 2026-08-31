#include <iostream>
#include <vector>

int euler_phi(int n, std::vector<int> const &primes) {
  int reduced = n, result = n;
  for (auto &p : primes) {
    if (p * p > reduced)
      break;

    if (reduced % p)
      continue;

    while (reduced % p == 0)
      reduced /= p;

    result -= result / p;
  }
  if (reduced > 1) {
    return result - result / reduced;
  } else {
    return result;
  }
}

std::vector<int> primes_to_sq(int maxN) {
  std::vector<int> primes = {2};
  for (int i = 3; primes.back() * primes.back() <= maxN; i += 2) {
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
  return primes;
}

int main() {
  int maxD = 1000000;
  auto primes = primes_to_sq((maxD));

  long long farey_len = -1;
  for (int i = 1; i <= maxD; i++) {
    farey_len += euler_phi(i, primes);
  }
  std::cout << farey_len << std::endl;
}
