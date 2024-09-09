#include<iostream>
#include<iomanip>
#include<cmath>

int main(){
    long long s = 10203040506070809;
    int counter[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for(int i = 1; i < 2; i ++){
        double tmp = s;
        for(int j = 0, k = 10; j < 10; j++, k*= 100){
            tmp += counter[j] * k;
        }
        std::cout << std::setprecision(30) << tmp << std::endl; 
    }
    return 0;
}