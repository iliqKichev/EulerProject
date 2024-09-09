#include <algorithm>
#include<iostream>
#include<vector>
using namespace std;

bool is_prime(int number){
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

bool is_in(vector<int> primes, int number){
    int lower_bound = 2;
    int upper_bound = primes.size();
    int middle;
    while(lower_bound != upper_bound - 1){
        middle = (upper_bound - lower_bound)/2 + lower_bound;
        if (primes[middle] > number){
            upper_bound = middle;
        }
        if (primes[middle] <= number){
            lower_bound = middle;
        }
    }
    return primes[lower_bound] == number;
}

std::vector<int> get_family(int number){
    short digit[10] = {0};
    int tmp = number;
    while(tmp > 0){
        digit[tmp%10] ++;
        tmp /= 10;
    }

}

int main(){
    int lowest_digit = 0;
    vector<int> primes;
    vector<int> prime_families[1<<6];
    int lower_bound=100000, upper_bound=lower_bound*10;
    cout << "Generating all primes from " << lower_bound << " up to " << upper_bound << "\n";
//    for(int i=lower_bound/10; i < upper_bound/10; i++){
//        int tmp[] = {i*10 + 1, i*10 + 3, i*10 + 7, i*10 + 9};
//        for(int p: tmp){
//            if(is_prime(p)){
//                int tmp = p;
//                int digits[10] = {0,0,0,0,0,0,0,0,0,0};
//                while(tmp > 0){
//                    digits[tmp%10] ++;
//                    tmp /= 10;
//                }
//                if(digits[0] > 1 || digits[1] > 1 ||
//                   digits[2] > 1 || digits[3] > 1 ||
//                   digits[4] > 1 || digits[5] > 1 ||
//                   digits[6] > 1 || digits[7] > 1 ||
//                   digits[8] > 1 || digits[9] > 1 ){
//                    primes.push_back(p);
//                }
//                if(digits[0] > 1 || digits[1] > 1 ||
//                   digits[2] > 1 ){
//                    potential.push_back(p);
//                }
//            }
//        }
//    }
    for(int i = lower_bound; i < upper_bound; i ++){
        
    }
    cout << "Evaluating potential candidates: " << potential.size() << "\n";
    cout << "Total primes with repeating digits: " << primes.size() << "\n";
    for(int p: primes){cout << p << " ";} cout << endl;
//    for(int p: potential){
//        int counter = 0;
//        for(int i = 0; i < 10; i ++){
//            if(is_in(primes, replace(p, lowest_digit, i))){
//                counter ++;
//            }
//        }
//        if(counter == 8){
//            cout << p << " " << counter << endl;
//        }
//    }
    return 0;
}
