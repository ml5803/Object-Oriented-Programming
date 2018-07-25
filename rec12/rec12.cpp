// Doubly linked list

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    struct Node{
        Node(int data, Node* prior = nullptr, Node* next = nullptr): data(data), prior(prior), next(next){}
        Node* prior;
        Node* next;
        int data;
    };

    friend ostream& operator<<(ostream& os, const Node* node){
        os << node->data;
        return os;
    }
public:
    class iterator{
        friend class List;
    public:
        iterator(Node* node): node(node){}
        iterator& operator++(){
            node = node->next;
            return *this;
        };
        iterator& operator--(){
            node = node->prior;
            return *this;
        };
        bool operator==(const iterator& rhs){
            return node == rhs.node;
        };
        bool operator!=(const iterator& rhs){
            return node != rhs.node;
        };
        int& operator*(){
            return node->data;
        };
    private:
        Node* node;
    };

    friend ostream& operator<<(ostream& os, const List& lst){
        Node* curr = lst.head->next;
        while(curr != lst.tail){
            os << curr->data << " ";
            curr = curr->next;
        }
        return os;
    }
    List(): head(new Node(0)), tail(new Node(0)){
        head->next = tail;
        tail->prior = head;
    }

    List(const List& rhs): head(new Node(0)), tail(new Node(0)){
        head->next = tail;
        tail->prior = head;

        for(List::iterator iter = rhs.begin(); iter != rhs.end(); ++iter){
            this->push_back(iter.node->data);
        }
    }

    List operator=(const List& rhs){
        clear();
        for(List::iterator iter = rhs.begin(); iter != rhs.end(); ++iter){
            this->push_back(iter.node->data);
        }
        return *this;
    }

    ~List(){
        clear();
        delete head;
        delete tail;
    }
    void push_back(int data){
        Node* newNode = new Node(data);
        Node* prev = tail->prior;
        newNode->next = tail;
        newNode->prior = prev;
        prev->next = newNode;
        tail->prior = newNode;
        length+=1;
    };
    void pop_back(){
        Node* nodeToDelete = tail->prior;
        Node* beforeNode = nodeToDelete->prior;
        tail->prior = beforeNode;
        beforeNode->next = tail;
        delete nodeToDelete;
        length-=1;
    };

    void push_front(int data){
        Node* newNode = new Node(data);
        Node* following = head->next;
        newNode->prior = head;
        newNode->next = following;
        following->prior = newNode;
        head->next = newNode;
        length+=1;
    };

    void pop_front(){
        Node* nodeToDelete = head->next;
        head->next = nodeToDelete->next;
        nodeToDelete->next->prior = head;
        delete nodeToDelete;
        length-=1;
    };

    void clear(){
        while(length>0){
            pop_back();
        }
    }

    const int& operator[](int ind) const{
        if(ind > length){
            cout << "out of bounds" << endl;
        }

        Node* curr = head->next;
        int counter = 0;
        while (counter < ind){
            //cout << "Index: " << counter << endl;
            curr = curr->next;
            counter+=1;
        }
        return curr->data;
    }

    int& operator[](int ind){
        if(ind > length){
            cout << "out of bounds" << endl;
        }

        Node* curr = head->next;
        int counter = 0;
        while (counter < ind){
            //cout << "Index: " << counter << endl;
            curr = curr->next;
            counter+=1;
        }
        return curr->data;
    }

    iterator insert(const iterator& iter, int data){
        Node* newNode = new Node(data);
        Node* currNode = iter.node;
        Node* prevNode = currNode->prior;
        newNode->next = currNode;
        newNode->prior = prevNode;
        currNode->prior = newNode;
        prevNode->next = newNode;
        length+=1;
        return iterator(newNode);
    }

    iterator erase(const iterator& iter){
        Node* currNode = iter.node;
        Node* prevNode = currNode->prior;
        Node* nextNode = currNode->next;
        prevNode->next = nextNode;
        nextNode->prior = prevNode;
        delete currNode;
        length-=1;
        return iterator(nextNode);
    }

    int& front(){
        return (head->next)->data;
    };
    int& back(){
        return (tail->prior)->data;
    };
    size_t size(){
        return length;
    };

    iterator begin(){
        return iterator(head->next);
    };

    iterator end(){
        return iterator(tail);
    };

    iterator begin() const{
        return iterator(head->next);
    };

    iterator end() const{
        return iterator(tail);
    };
private:
    Node* head;
    Node* tail;
    size_t length = 0;
};

void printListInfo(List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";

    // Task3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
//    cout << myList << endl;
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
//    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;

//    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    printListInfo(myList);
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
}
