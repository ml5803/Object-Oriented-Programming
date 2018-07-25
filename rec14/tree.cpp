//#include <iostream>
//using namespace std;
//
//struct TNode {
//  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
//    : data(data), left(left), right(right) {}
//  int data;
//  TNode *left, *right;
//};
//
//int max(TNode* root) {
//  // Provide this code
//    int maxRight;
//    int maxLeft;
//
//    //if no childs, return self
//    if(!root->left && !root->right){
//        return root->data;
//    }
//
//    //only right child
//    if(!root->left){
//        maxRight = max(root->right);
//        if(maxRight > root->data){
//            return maxRight;
//        }else{
//            return root->data;
//        }
//    }
//
//    //only left child
//    if(!root->right){
//        maxLeft = max(root->left);
//        if(maxLeft > root->data){
//            return maxLeft;
//        }else{
//            return root->data;
//        }
//    }
//
//    //both children exist
//    maxLeft = max(root->left);
//    maxRight = max(root->right);
//    if(maxLeft > maxRight){
//        if (maxLeft > root->data){
//            return maxLeft;
//        }else{
//            return root->data;
//        }
//    }
//    if(maxRight>maxLeft){
//        if (maxRight > root->data){
//            return maxRight;
//        }else{
//            return root->data;
//        }
//    }
//
//    return root->data;
//}
//
////int main() {
////    TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
////    cout << "max of tree is: " << max(&f) << endl;
////
////}
//
//
//
