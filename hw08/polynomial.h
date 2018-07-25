#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

void listAddHead(Node*& headPtr, int data);
int listLength(Node* headPtr);
void listDisplay(Node* headPtr);

class Polynomial{
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
public:
    Polynomial(const std::vector<int>& vecCoeff);
    Polynomial(const Polynomial& rhs);
    Polynomial& operator=(const Polynomial& rhs);
    ~Polynomial();
    Polynomial& operator+=(const Polynomial& rhs);
    std::string makeDisplay(Node* currNode, int deg) const;
    int evaluate(int val) const;
    void normalize(Node* prev, Node* curr);
private:
    Node* lstCoeff;
    int degree;
};

#endif // POLYNOMIAL_H_INCLUDED
