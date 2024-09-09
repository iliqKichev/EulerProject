#include<iostream>
#include<unordered_map>

using namespace std;

int main(){
    unsigned long long  curr=15041707150417070, MOD = 4503599627370517, step = 1504170715041707;
    unsigned long long sum = 0;
    unsigned long long first = 0;
    std::cout << MOD / step << std::endl;
    unordered_map<string, bool> euler;
    while(true){
        unsigned long long n = (MOD - first) /( 3 * step - MOD);
        std::cout << n << std::endl;
        sum += n*(n-1) / 2 * (3 * step - MOD) + first;
        first = (first + (3 * step - MOD) * (n+1)) % MOD;
        if(first == 0) break;
    }

    std::cout << sum << std::endl;
    return 0;
}
