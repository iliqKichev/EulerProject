#include<iostream>
#include<gmpxx.h>
using namespace std;

// Idea!
// All of the possible divisions of abcdefgh... are coded in 2^<number of digits - 1> sums (there is division between every two digits or there is not)
// Thus, if we iterate over all of the possible divisions, we could determine if a number is an S number.
// Let 1 mean division between the two digits and 0 mean no division. Let every bit of the number "splits" mean exactly that.
bool is_S(string number, int root){
    int splits = (1<<(number.size())) - 1;
    while(splits > 0){
        int p = 1<<(number.size()), tmp = 0, sum = 0, i = 0;
        while(p > 0){
//            cout << sum << " " << tmp << " " << splits << " " << p << endl;
            if(p & splits){
                sum += tmp;
                tmp = 0;
            }
            else{
                tmp *= 10;
            }
            tmp += number[i] - '0';
            i++;
            p >>= 1;
        }
        if(sum == root){
            return true;
        }
        splits -= 2;
    }
    return false;
}

int main(){
    mpz_class sum = 0;
//    cout << is_S("8100", 90) << endl;
    for(int i = 2; i <= 1000000; i ++){
        mpz_class n = i; n *= n; // Square of i
        string digits = n.get_str();
        if(is_S(digits, i)){sum += n;
        cout << i << endl;}
    }
    cout << sum << "\n";
    return 0;
}
