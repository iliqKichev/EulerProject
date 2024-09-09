#include<iostream>
#include<gmpxx.h>

using namespace std;

class Fraction{
    private:
        mpz_class den, num;
    public:
        Fraction(mpz_class num = 0, mpz_class den = 1){
            this->num = num;
            this->den = den;
        }

        void simplify(){
            mpz_class g = gcd(this->den, this->num);
            this->den /= g;
            this->num /= g;
        }

        void reverse(){
            swap(this->den, this->num);
        }

        bool has_more_digits(){
            return den.get_str().size() < num.get_str().size();
        }

        void print(){
            cout << this->num << "/" << this->den;
        }

        friend Fraction operator+(Fraction lhs, Fraction rhs);
};

Fraction operator+(Fraction lhs, Fraction rhs){
    Fraction ans(lhs.num*rhs.den + rhs.num*lhs.den, lhs.den*rhs.den);
    ans.simplify();
    return ans;
}

int main(){
    Fraction a(1, 1), b(1, 1);
    int counter = 0;
    for(int i = 0; i <= 1000; i ++){
        a.print(); cout << " " << i << "\n";
        if(a.has_more_digits()) counter ++;
        a = a + b;
        a.reverse();
        a = a + b;
    }
    cout << counter << endl; 
    return 0;
}
