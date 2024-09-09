#include<iostream>
#include<vector>
#include<cmath>
#include <iomanip>
#include <gmpxx.h>

# define A 800

mpz_class A_LN_A_MPZ;
bool check_if_fits_mpz(const int p, const int q){
    mpz_class n, m;
    mpz_ui_pow_ui(n.get_mpz_t(), p, q);
    mpz_ui_pow_ui(m.get_mpz_t(), q, p);
    n *= m;
    return n <= A_LN_A_MPZ;
}

const double A_LN_A = log(800800)*800800;    
bool check_if_fits(const int q, const int p){
    return log(q) * p + log(p) * q <= A_LN_A;
}

int main(){
    // mpz_ui_pow_ui(A_LN_A_MPZ.get_mpz_t(), 800800, 800800);
    std::vector<int> primes;
    int beg = 3, end = 1<<31;
    int mid = beg + (end-beg)/2;
    while(beg < mid){
        if(check_if_fits(mid, 2)) beg = mid;
        else end = mid;
        mid = beg + (end-beg)/2;
    }
    primes.reserve(beg);
    primes.push_back(2);
    for(int i = 3; i <= beg; i += 2){
        bool key = true;
        for(int j = 3; j*j <= i; j +=2){
            
            if(i%j == 0){
                key = false;
                break;
            }
        }
        // std::cout << std::endl;
        if(key){
            primes.push_back(i);
        }
    } 
    unsigned long long sum = 0;
    for(int i = 0; 2*i < primes.size(); i ++){
        beg = i, end = primes.size();
        mid = beg + (end - beg) / 2;
        while(beg < mid){
            if(check_if_fits(primes[mid], primes[i])){
                beg = mid;
            }
            else{
                end = mid;
            }   
            mid = beg + (end - beg) / 2;
        }
        if(beg-i) std::cout << i+1 << " " << primes[i] << " " << beg-i << " beg\n";
        if(beg < primes.size())sum += beg-i;
    }
    std::cout << primes.size() << std::endl;
    std::cout << sum << std::endl;
    return 0;
}