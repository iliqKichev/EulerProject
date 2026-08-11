#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>

bool is_i_in(long long num, int i){
  long long tmp = num;
  while(tmp > 0){
    if(tmp % 10 == i){
      return true;
    }
    tmp /= 10;
  }
  return false;
}

int sub(long long num, int i, std::unordered_set<long long> &primes) {
  if (!is_i_in(num, i)) return -1;
  
  int fam_size = 0;
  for (int j = 0; j < 10; j++) {
    std::string n = std::to_string(num);
    std::replace(n.begin(), n.end(), '0' + i, '0' + j);
    fam_size += primes.find(std::stoll(n)) != primes.end();
  }
  return fam_size;
}

int main() {
  std::unordered_set<long long> primes_lb = {2}, primes;
  long long ub = 1000001;
  long long lb = 100001;
  for (long long i = 3; i < lb; i += 2) {
    bool flag = true;
    for (auto p : primes_lb) {
      if (i % p == 0) {
        flag = false;
        break;
      }
    }
    if (flag) {
      primes_lb.insert(i);
    }
  }

  for (long long i = lb; i < ub; i += 2) {
    bool flag = true;
    for (auto p : primes_lb) {
      if (i % p == 0) {
        flag = false;
        break;
      }
    }
    if (flag) {
      for (auto p : primes) {
        if (i % p == 0) {
          flag = false;
          break;
        }
      }
    }
    if (flag) {
      primes.insert(i);
    }
  }
  long long min_num_fam_size8 = ub;
  for (auto p : primes) {
    int max_fam_size = -1;
    for (int i = 0; i < 10; i++) {
      max_fam_size = std::max(max_fam_size, sub(p, i, primes));
    }
    if (max_fam_size == 8){
      min_num_fam_size8 = std::min(min_num_fam_size8, p);
      // std::cout << max_fam_size << " " << p << std::endl;
      }
  }
  std::cout << min_num_fam_size8 << std::endl;
  return 0;
}
