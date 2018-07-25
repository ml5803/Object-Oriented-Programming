#include <iostream>
#include <stdexcept>

using namespace std;

struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

void listAddAfter(Node*& node, int data) {
    Node* after = new Node(data);
    node->next = after;
}

int listLength(Node* headPtr){
    Node* p = headPtr;
    int counter = 0;
    while (p != nullptr) {
        ++counter;
        p = p->next;
    }
    return counter;
}

void listDisplay(Node* headPtr){
    Node* p = headPtr;
    while (p != nullptr) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

struct TNode {
  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
  int data;
  TNode *left, *right;
};

int max(TNode* root) {
    if(!root){
        throw(logic_error("Tree is empty"));
    }
    int maxRight;
    int maxLeft;

    //if no childs, return self
    if(!root->left && !root->right){
        return root->data;
    }

    //only right child
    if(!root->left){
        maxRight = max(root->right);
        if(maxRight > root->data){
            return maxRight;
        }else{
            return root->data;
        }
    }

    //only left child
    if(!root->right){
        maxLeft = max(root->left);
        if(maxLeft > root->data){
            return maxLeft;
        }else{
            return root->data;
        }
    }

    //both children exist
    maxLeft = max(root->left);
    maxRight = max(root->right);
    if(maxLeft > maxRight){
        if (maxLeft > root->data){
            return maxLeft;
        }else{
            return root->data;
        }
    }
    if(maxRight>maxLeft){
        if (maxRight > root->data){
            return maxRight;
        }else{
            return root->data;
        }
    }

    return root->data;
}

bool evenBits(int num){
    if (num == 0){
        return true;
    }

    //if I include an extra bit
    if (num%2 == 1){
        if(evenBits(num/2)){
            return false;
        }else{
            return true;
        }
    }

    //no extra bit
    return evenBits(num/2);
}

Node* addLists(Node* lst1, Node* lst2){
    if (!lst1 && !lst2){
        return nullptr;
    }

    Node* newNode = new Node();
    if(!lst2){
        newNode->data = lst1->data;
        newNode->next = addLists(lst1->next,nullptr);
        return newNode;
    }

    if(!lst1){
        newNode->data = lst2->data;
        newNode->next = addLists(lst2->next,nullptr);
        return newNode;
    }

    newNode->data = lst1->data + lst2->data;
    newNode->next = addLists(lst1->next,lst2->next);
    return newNode;
}

bool palindrome(char* strChars, size_t siz){
    if(siz < 2)
        return true;
    //cout << *strChars << " " << *(strChars+siz-1) << endl;
    if (*strChars == *(strChars+siz-1)){
        return palindrome(strChars+1,siz-2);
    }else{
        return false;
    }
}

int hanoi(int plates, const string& source, const string& spare, const string& target){
    if(plates == 0){
        return 0;
    }else{
        return hanoi(plates-1, source, spare, target) + hanoi(plates-1, spare, source, target) + 1;
    }
}


void mystery(int n) {
   if (n > 1) {
      cout << 'a';
      mystery(n/2);
      cout << 'b';
      mystery(n/2);
   }
   cout << 'c';
}

int main()
{
    cout << "======evenBits test======" << endl;
    cout << boolalpha;
    cout << "evenBits(0): " << evenBits(0) << endl;
    cout << "evenBits(1): " << evenBits(1) << endl;
    cout << "evenBits(2): " << evenBits(2) << endl;
    cout << "evenBits(6): " << evenBits(6) << endl;
    cout << "evenBits(32): " << evenBits(32) << endl;

    cout << endl << "======addLists test======" << endl;
    Node* three = new Node(3,nullptr);
    Node* two = new Node(2,three);
    Node* one = new Node(1, two);

    Node* five = new Node(5,nullptr);
    Node* four = new Node(4, five);

    cout << "List1 : 1 2 3" << endl;
    cout << "List2 : 4 5" << endl;
    cout << "Combined list is: ";
    listDisplay(addLists(one,four));

    cout << endl << "======max tree test======" << endl;
    TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
    try{
        //cout << "max of empty tree is: " << max(nullptr) << endl;
        cout << "max of tree is: " << max(&f) << endl;
    }catch(logic_error){
        cerr << "No max in empty tree" << endl;
    }

    cout << endl << "======palindrome test======" << endl;
    char noon[] = "noon";
    char test[] =  "teTet";
    char none[] = "none";
    cout << "noon - " << palindrome(noon,4) << endl;
    cout << "teTet - " << palindrome(test,5) << endl;
    cout << "none - " << palindrome(none,4) << endl;

    cout << endl << "======hanoi count test======" << endl;
    cout << "hanoi(1,a,b,c) " << hanoi(1,"a","b","c") << endl;
    cout << "hanoi(2,a,b,c) " << hanoi(2,"a","b","c") << endl;
    cout << "hanoi(3,a,b,c) " << hanoi(3,"a","b","c") << endl;
    cout << "hanoi(4,a,b,c) " << hanoi(4,"a","b","c") << endl;

    cout << endl << "======It?s?a?mystery?======" << endl;
    for(int i = 0; i < 11 ;++i){
        mystery(i);
        cout << endl;
    }
}
