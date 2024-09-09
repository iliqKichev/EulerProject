#include<iostream>

using namespace std;

bool is_prime(int number){
    if(number < 2) return false;
    if(number % 2 == 0 && number > 2){
        return false;
    }
    for(int i=3; i*i <= number; i+=2){
        if(number % i == 0){
            return false;
        }
    }
    return true;
}

int main(){
    double primes_in_diagonals = 0;
    int side = 1;
    for(side = 3; side<100000000; side += 2){
        if(is_prime((side-2)*(side-2) + side - 1)) primes_in_diagonals ++;
        if(is_prime((side-2)*(side-2) + 2*side - 2)) primes_in_diagonals ++;
        if(is_prime((side)*(side) - side + 1)) primes_in_diagonals ++;
        cout << side << " " << primes_in_diagonals << " " <<  (2*side - 1) << " " << primes_in_diagonals / (2*side - 1) << endl;
        if(primes_in_diagonals / (2*side - 1) < 0.1){
            cout << side << endl;
            return 0;
        }
    }
}
