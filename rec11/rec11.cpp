#include <vector>
#include <string>
#include <iostream>
#include <cstdlib> // To allow NULL if no other includes
using namespace std;

struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};

void listInsertHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

// Should free up your nodes, of course...
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// This might be useful for setting up test cases. Feel free to use it
// or not as you like. Example of using would be:
// Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listInsertHead(result, vals[index-1]);
    }
    return result;
}

void printLinked(Node* node){
    Node* curr = node;
    while (curr){
        cout << curr->data << " ";
        curr = curr->next;
    }
}

void spliceList(Node*& nodeToSpliceAfter, Node* linkL){
    if (!linkL){
        return;
    }
    if (!nodeToSpliceAfter){
        nodeToSpliceAfter = linkL;
    }else{
        Node* next = nodeToSpliceAfter->next; //node after the insert part
        nodeToSpliceAfter->next = linkL;
        while(linkL->next){
            linkL = linkL->next; //bump the pointer to last item in linkL
        }
        linkL->next = next;
    }
}

Node* isSubList(Node* link, Node* subList){
    cout << endl;
    Node* startNode = nullptr; //return start of the chain
    Node* startCheck = subList;
    Node* curr = link;
    Node* currSub = subList;
    while(link->next){//go through entire list
        if(link->data == startCheck->data){//if there is a matching
            cout << "First match " << link->data << endl;
            startNode = link;
            curr = link;
            currSub = startCheck;
            while(currSub){//go through secondList
                if(curr->data != currSub->data){ //if there was a chain and the chain is now broken
                    cout << "The chain died :(" << endl;
                    currSub = startCheck;
                    startNode = nullptr;
                    link = link->next;
                    // curr = link;
                    break;
                }
                if (curr->next==nullptr && currSub->next){
                    return nullptr;
                }
                if (curr->data == currSub->data && currSub->next == nullptr){//went to last check and completed
                    cout << "Matching completed! It exists" << endl;
                    return startNode;
                }
                if(curr->data == currSub->data){//if matched, check next
                    //cout << "Another match: " << curr->data << endl;
                    curr=curr->next;
                    currSub=currSub->next;
                }
            }
           // return startNode;
        }else{
            link = link->next;
        }
    }
    return startNode;
}

int main(){
    //Task 1
    cout << "Linked List 1: ";
    Node* link1 = listBuild({1,2,3,2,3,2,4,5,6});
    printLinked(link1);
    cout << endl << "Linked List 2: ";
    Node* link2 = listBuild({5,6,7});
    printLinked(link2);
//    spliceList(link1, link2);
//    cout << endl << "Spliced Linked List: ";
    //printLinked(link1);
    //Task 2

    Node* start = isSubList(link1,link2);
    if(start){
        cout << endl << "Item found: The start node has value ";
        printLinked(start);
    }else{
        cout << endl << "Failed to match" << endl;
    }
}
