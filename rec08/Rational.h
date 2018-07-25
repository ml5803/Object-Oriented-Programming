#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED

#include <string>
#include <iostream>

namespace CS2124{
    class Rational{
    public:
        friend std::ostream& operator<<(std::ostream& os, const Rational& rat);
        friend std::istream& operator>>(std::istream& is, Rational& rat);
        friend bool operator==(const Rational& lhs, const Rational& rhs);
        Rational(int num = 0, int denom = 1): num(num), denom(denom){
            normalize();
        }
        void normalize();
        Rational& operator+=(const Rational& rhs);
        Rational& operator++();
        Rational operator++(int);
        explicit operator bool() const;
    private:
        int num;
        int denom;
        int greatestCommonDivisor(int x, int y);
        void negativeModify();
    };

    Rational operator+(const Rational& lhs, const Rational& rhs);
    bool operator==(const Rational& lhs, const Rational& rhs);
    bool operator!=(const Rational& lhs, const Rational& rhs);
    Rational& operator--(Rational& rat);
    Rational operator--(Rational& rat, int);
}
#endif // RATIONAL_H_INCLUDED
