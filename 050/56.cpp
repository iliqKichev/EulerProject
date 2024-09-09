#include<iostream>
#include<gmpxx.h>
using namespace std;

mpz_class pow(int base, int power){
    mpz_class ans = 1, p = base;
    for(int i = 1; i <= power; i <<= 1){
        if(power & i){
            ans *= p;
        }
        p *= p;
    }
    return ans;
}

int sum_of_digits(mpz_class number){
    string digits = number.get_str();
    int ans = 0;
    for(char d: digits){
        ans += d - '0';
    }
    return ans;
}
int main(){
    int max_sum = -1;
    for(int a = 1; a < 100; a ++){
        for(int b = 2; b < 100; b ++){
            max_sum= std::max(max_sum, sum_of_digits(pow(a, b)));
        }
    }
    cout << max_sum << endl;
    return 0;
}
