#include<iostream>
#include<iomanip>
#include<gmpxx.h>

using namespace std;

int main(){
    mpf_set_default_prec(1024);
    mpf_class n;
    int sum = 0;
    for(mpf_class i = 1; i <= 100; i ++){
        n = sqrt(i);
        // is the sqrt irrational
        if(floor(n) < n){
            mp_exp_t mp_exp;
            string digits = n.get_str(mp_exp);
            for(int d = 0; d < 100; d ++){
                if(digits[d] != '.') sum += digits[d] - '0';
            }
        }
    }
    cout << sum << " SUM\n";
    return 0;
}
