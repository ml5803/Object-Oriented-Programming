//#include "polynomial.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

void listAddHead(Node*& headPtr, int data) {
    // 1. make a node for the data
    Node* p = new Node(data);
    // 2. have the node "point to" the old head
    p->next = headPtr;
    // 3. have the headPtr point to the new node
    headPtr  = p;
}

int listLength(Node* headPtr) {
    Node* p = headPtr;
    int counter = 0;
    while (p != nullptr) {
        ++counter;
        p = p->next;
    }
    return counter;
}

void listDisplay(Node* headPtr) {
    //void listDisplay(const Node* headPtr) {
    Node* p = headPtr;
    //const Node* p = headPtr;
    //while (p->next != nullptr) {
    while (p != nullptr) {
    //while (p) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

class Polynomial{
    friend ostream& operator<<(ostream& os, const Polynomial& poly);
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
public:
    Polynomial(const vector<int>& vecCoeff = {0}):lstCoeff(nullptr), degree(0){
        size_t counter = 0;
        //find first non-zero
        while (vecCoeff[counter] == 0){
            //cout << vecCoeff[counter];
            counter++;
            //if looped through and all 0, put 0 as polynomial
            if (counter == vecCoeff.size()){
                listAddHead(lstCoeff,0);
                degree++;
                break;
            }
        }

        for(size_t i = counter; i < vecCoeff.size(); ++i ){
            listAddHead(lstCoeff,vecCoeff[i]);
            degree++;
        }
        //cout << listLength(lstCoeff) << endl;
    }

    Polynomial(const Polynomial& rhs):lstCoeff(new Node(rhs.lstCoeff->data,nullptr)), degree(rhs.degree){
        Node* myCoeff = this->lstCoeff;
        Node* otherCoeff = rhs.lstCoeff->next;

        //set next of prior node as it builds
        while(otherCoeff){
            myCoeff->next = new Node(otherCoeff->data,nullptr);
            myCoeff = myCoeff->next;
            otherCoeff = otherCoeff->next;
        }
    }

    Polynomial& operator=(const Polynomial& rhs){
        if(&rhs != this){
            //if not self, clear and reassign
            Node* curr = lstCoeff;
            Node* next;
            while(curr){
                //cout << curr->data << " ";
                next = curr->next;
                delete curr;
                curr = next;
            }

            this->lstCoeff = new Node(rhs.lstCoeff->data,nullptr);
            this->degree = rhs.degree;
            Node* myCoeff = this->lstCoeff;
            Node* otherCoeff = rhs.lstCoeff->next;

            //set next of prior node as it builds
            while(otherCoeff){
                myCoeff->next = new Node(otherCoeff->data,nullptr);
                myCoeff = myCoeff->next;
                otherCoeff = otherCoeff->next;
            }
        }
        return *this;
    }

    ~Polynomial(){
        //cout << "Now destroying: ";
        Node* curr = lstCoeff;
        Node* next;
        while(curr){
            //cout << curr->data << " ";
            next = curr->next;
            delete curr;
            curr = next;
        }
        //cout << endl;
    }

    Polynomial& operator+=(const Polynomial& rhs){
        Node* myNode = this->lstCoeff;
        Node* otherNode = rhs.lstCoeff;

        // if other degree is greater, need to adjust after math
        if (rhs.degree > this->degree){
            this->degree = rhs.degree;
        }

        //1 before the end of polynomial
        while (myNode->next && otherNode->next){
            myNode->data += otherNode->data;
            myNode=myNode->next;
            otherNode=otherNode->next;
        }
        myNode->data += otherNode->data;

        //same length then done
        if(myNode->next == nullptr && otherNode->next == nullptr){
            listDisplay(lstCoeff);
            return *this;
        }

        //if other one is longer
        if(myNode->next == nullptr){
            otherNode=otherNode->next;
            while(otherNode){
                myNode->next = new Node(otherNode->data,nullptr);
                myNode=myNode->next;
                otherNode=otherNode->next;
            }
        }
        //if this longer, do nothing
        return *this;
    }

    string makeDisplay(Node* currNode, int deg) const{
        string stringVal = "";
        //case largest coefficient, no + in front
        if(currNode->next == nullptr){
            //if degree = 0, get coefficient
            if (deg == 0){
                return to_string(currNode->data);
            }
            //if degree = 1, get coefficient + x
            if (deg == 1){
                if (currNode->data == 0){
                    return "";
                }else{
                    if (currNode->data == 1){
                        return "x";
                    }else{
                        return to_string(currNode->data) + "x";
                    }
                }
            }
            //otherwise
            //FIX if largest coefficient is 1, use exponents
            if (currNode->data == 0){
                return "";
            }else{
                if (currNode->data == 1){
                    return "x^" + to_string(deg);
                }else{
                    return to_string(currNode->data) + "x^" + to_string(deg);
                }
            }
        }else{
            //if data is 0, go on to next node
            if(currNode->data == 0){
                return makeDisplay(currNode->next,deg+1) + stringVal;
            }

            stringVal += "+";

            //Only case where 1 needs to be displayed is if it is the last constant term
            if (currNode->data == 1 && deg == 0){
                stringVal += "1";
            }

            if (currNode->data != 1){
                stringVal += to_string(currNode->data);
            }
            //if degree 1, no exponents
            if(deg == 1){
                stringVal += "x";
            }else{
                if(deg > 0){
                    stringVal += "x^" + to_string(deg);
                }
            }
            return makeDisplay(currNode->next,deg+1) + stringVal;
        }
    }

    int evaluate(int val){
        int result = 0;
        int degree = 0;
        int product = 1;
        Node* curr = this->lstCoeff;
        while(curr){
            for(int counter = 0; counter < degree; ++counter){
                product *= val;
            }
            result += curr->data * product;
            curr=curr->next;
            degree+=1;
            product = 1;
        }
        return result;
    }

    void normalize(){
    }
private:
    Node* lstCoeff;
    int degree;
};

void doNothing(Polynomial temp) {}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial newPoly(lhs);
    newPoly += rhs;
    return newPoly;
};

ostream& operator<<(ostream& os, const Polynomial& poly){
    os << poly.makeDisplay(poly.lstCoeff,0);
    return os;
}
bool operator==(const Polynomial& lhs, const Polynomial& rhs){
    if(lhs.degree != rhs.degree){
        return false;
    }

    Node* lhsNode = lhs.lstCoeff;
    Node* rhsNode = rhs.lstCoeff;

    while(lhsNode && rhsNode){
        if(lhsNode->data != rhsNode->data){
            return false;
        }
        lhsNode=lhsNode->next;
        rhsNode=rhsNode->next;
    }

    return true;
}
bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs==rhs);
}

int main() {

    //test constructor
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -1x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7
//    Polynomial zeroFirst({0,0,0,0,1});
//    Polynomial allZero({0,0,0,0,0});
//    Polynomial midZero({1,2,0,4,5});
//    Polynomial trailZero({1,0,0,0,0});

    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 << endl;
    cout << "has_a_zero: " << has_a_zero << endl;
//    cout << "zeroFirst: " << zeroFirst << endl;
//    cout << "allZero: " << allZero << endl;
//    cout << "midZero: " << midZero << endl;
//    cout << "trailZero: " << trailZero << endl;
    cout << "This one buggy --- p2 + p3: " << (p2+p3) << endl;
    cout << "p2 + p4: " << (p2+p4) << endl;
    cout << "p4 + p2: " << (p4+p2) << endl;


    //test copy constructor - the statement below uses the copy constructor
    //to initialize poly3 with the same values as poly4
    Polynomial p5(p4);
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;
    cout << "p5: " << p5 << endl;

    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    //tests the assignment operator
    Polynomial p6;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
    p6 = p4;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
//
//    //test the evaluaton
    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;

    Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p7: " << p7 << endl;
    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;
}


