#include <iostream>
#include <vector>

int main() {
  std::vector<int> P(1024, 0), primes = {2};
  P[0] = 1;

  for (int i = 3; i < 10000; i += 2) {
    bool flag = true;
    for (int j = 0; j < primes.size() && primes[j] * primes[j] <= i; j++) {
      if (i % primes[j] == 0) {
        flag = false;
        break;
      }
    }
    if (flag)
      primes.push_back(i);
  }
  
  for(int i = 0; i < primes.size(); i ++){
    for(int k = primes[i]; k < P.size(); k ++){
      P[k] += P[k-primes[i]];
    } 
  }

  for(int i = 0; i < P.size(); i ++){
    if(P[i] >= 5000){
      std::cout << i << std::endl;
      return 0;
    }
  }

  return 0;
}
