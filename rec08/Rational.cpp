#include "Rational.h"
#include <iostream>

using namespace std;

namespace CS2124{
    void Rational::normalize(){
        int factor;
        negativeModify();
        int tempSign;
        if(num >=0){
            tempSign = 1;
        }else{
            tempSign = -1;
        }
        factor = greatestCommonDivisor(tempSign * num, denom);
        if (factor != 1){
            num = num/factor;
            denom = denom/factor;
        }
    }

    Rational& Rational::operator+=(const Rational& rhs){
        //cout << "Me: " << *this << " Other: " << rhs << endl;
        int newDenom = this->denom * rhs.denom;
        num = num * rhs.denom + rhs.num * this->denom;
        denom = newDenom;
        this->normalize();
        return *this;
    }

    Rational& Rational::operator++(){
        num+=denom;
        return *this;
    }

    Rational Rational::operator++(int){
        Rational rat = *this;
        num+=denom;
        return rat;
    }

    Rational::operator bool() const{
        return num!=0;
    }

    int Rational::greatestCommonDivisor(int x, int y) {
        while (y != 0) {
            int temp = x % y;
            x = y;
            y = temp;
        }
        return x;
    }

    void Rational::negativeModify(){
        if (num < 0 and denom < 0){ // -1/-2
            num = -1 * num;
            denom = -1 * denom;
            return;
        }
        if (num > 0 and denom < 0){ // 1/-2
            num = -1 * num;
            denom = -1 * denom;
            return;
        }
        // -1/2 and 1/2 doesn't need to be modified.
    }

    ostream& operator<<(ostream& os, const Rational& rat){
        os << rat.num << "/" << rat.denom;
        return os;
    };

    istream& operator>>(istream& is, Rational& rat){
        int num;
        int denom;
        char slash;
        is >> num;
        is >> slash;
        is >> denom;
        rat.num = num;
        rat.denom = denom;
        rat.normalize();
        return is;
    }

    Rational operator+(const Rational& lhs, const Rational& rhs){
        Rational rat = lhs;
        rat+=rhs;
        return rat;
    }

    bool operator==(const Rational& lhs, const Rational& rhs){
        if (lhs.num == rhs.num && lhs.denom == rhs.denom){
            return true;
        }else{
            return false;
        }
    }

    bool operator!=(const Rational& lhs, const Rational& rhs){
        return !(lhs==rhs);
    }

    Rational& operator--(Rational& rat){
        rat += -1;
        return rat;
    }

    Rational operator--(Rational& rat, int){
        Rational tempRat = rat;
        rat += -1;
        return tempRat;
    }
}
