/*
    Michael Li
	testRational.cpp
	CS2124
	Implement the class Rational, so that the following program works.
*/

#include <iostream>
#include <string>
//#include "Rational.h"
using namespace std;
//using namespace CS2124;

class Rational{
public:
    friend ostream& operator<<(ostream& os, const Rational& rat);

    friend istream& operator>>(istream& is, Rational& rat);

    friend bool operator==(const Rational& lhs, const Rational& rhs);

    Rational(int num = 0, int denom = 1): num(num), denom(denom){
        normalize();
    }

    void normalize(){
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

    Rational& operator+=(const Rational& rhs){
        //cout << "Me: " << *this << " Other: " << rhs << endl;
        int newDenom = this->denom * rhs.denom;
        num = num * rhs.denom + rhs.num * this->denom;
        denom = newDenom;
        this->normalize();
        return *this;
    }

    Rational& operator++(){
        num+=denom;
        return *this;
    }

    Rational operator++(int){
        Rational rat = *this;
        num+=denom;
        return rat;
    }

    explicit operator bool() const{
        return num!=0;
    }
private:
    int num;
    int denom;

    int greatestCommonDivisor(int x, int y) {
        while (y != 0) {
            int temp = x % y;
            x = y;
            y = temp;
        }
        return x;
    }

    void negativeModify(){
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
};
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

int main() {
    Rational twoThirds(-4,6);
    cout << twoThirds << endl;

    Rational a, b;
    cout << "Input two rational numbers.\n";
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    Rational one(1);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;

    //Implement as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
//
//     How does this manage to work?
//     It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
//
//     Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;
//
    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;
//
    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;
//
//     Even though the above example, (a++ ++), compiled, the
//     following shouldn't.
//     But some compiler vendors might let it...  Is your compiler
//     doing the right thing?
//     cout << "a-- -- = " << (a-- --) << endl;
//     cout << "a = " << a << endl;
//
//
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }
}
