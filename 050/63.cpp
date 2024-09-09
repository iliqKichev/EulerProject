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

int main(){
    int counter = 0;
    for(int b = 1; b < 10; b ++){
        for(int p = 1; p < 1000; p ++){
            mpz_class n = pow(b, p);
            if(n.get_str().size() == p){
                counter ++;
                cout << b << "^" << p << "=" << n << endl;
            }
        }
    }
    cout << counter << endl;
    return 0;
}
