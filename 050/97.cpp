#include<iostream>
#include<gmpxx.h>
using namespace std;

#define MOD 10000000000;

mpz_class pow(int power){
    mpz_class base = 2, ans = 1;
    int p = 1;
    while(p <= power){
        if(power & p){
            ans *= base;
            ans %= MOD;
        }
        p <<= 1;
        base *= base;
        base %= MOD;
    }
    return ans;
}

int main(){
    mpz_class b = pow(7830457);
    b *= 28433;
    b %= MOD;
    b += 1;
    b %= MOD;
    cout << b << endl;
    return 0;

}
