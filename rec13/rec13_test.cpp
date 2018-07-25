// rec13_test.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <set>         // task 20
#include <map>         // task 22
using namespace std;

void printListIter(const list<int>& l){
// DOESN'T WORK
//    for(list<int>::iterator iter = l.begin(); iter != l.end(); ++iter){
//        cout << *iter << " ";
//    }
}

void printListConstIter(const list<int>& l){
    for(list<int>::const_iterator iter = l.begin(); iter != l.end(); ++iter){
        cout << *iter << " ";
    }
}

void printListRangedFor(const list<int>& l){
    for(int num: l){
        cout << num << " ";
    }
}

void printOtherAuto(const list<int>& l){
    for(auto iter = l.begin(); iter != l.end(); ++++iter){
        cout << *iter << " ";
    }
}

list<int>::const_iterator myFind(const list<int>& l, int term){
    for(list<int>::const_iterator iter = l.begin(); iter != l.end(); ++iter){
        if(*iter == term){
            return iter;
        }
    }
    return l.end();
}

list<int>::const_iterator myFind2(const list<int>& l, int term){
    for(auto iter = l.begin(); iter != l.end(); ++iter){
        if(*iter == term){
            return iter;
        }
    }
    return l.end();
}

bool isEven(int n){
    return n%2 == 0;
}

struct findEven{;
    bool operator()(int n){
        return n%2 == 0;
    }
};

bool foundInVector(const vector<string>& v, const string& word){
    for(const string& w: v){
        if (w == word){
            return true;
        }
    }
    return false;
}
list<int>::const_iterator ourFind(const list<int>::iterator start, const list<int>::iterator ends, int term){
    cout << "THIS IS OURFIND!" << endl;
    for(auto iter = start; iter != ends; ++iter){
        if (*iter == term){
            return iter;
        }
    }
    return ends;
}

template <typename iters, typename term>
iters ourFind(const iters& start, const iters& ends,const term& lookFor){
    cout << "THIS IS OURFINDTEMPLATED!" << endl;
    for(auto iter = start; iter != ends; ++iter){
        if (*iter == lookFor){
            return iter;
        }
    }
    return ends;
}


int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> v = {3,2,1,4};
    for(int num: v){
        cout << num << " ";
    }
    cout << "\n=======\n";

    // 2. Initialize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> listOfNums(v.begin(),v.end());
    for(int num: listOfNums){
        cout << num << " ";
    }
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(v.begin(),v.end());
    for(int num: v){
        cout << num << " ";
    }
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for(size_t i = 0; i < v.size(); i=i+2){
        cout << v[i] << " ";
    }
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
//    for(size_t i = 0; i < listOfNums.size(); i=i+2){
//        cout << listOfNums[i] << " ";
//    }
    cout << "doesn't work" << endl;
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for(vector<int>::iterator i = v.begin(); i != v.end(); i=i+2){
        cout << *i << " ";
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for(list<int>::iterator iList = listOfNums.begin(); iList != listOfNums.end(); ++++iList){
        cout << *iList << " ";
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    listOfNums.sort();
    for(list<int>::iterator iList = listOfNums.begin(); iList != listOfNums.end(); ++iList){
        cout << *iList << " ";
    }
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printListConstIter(listOfNums);
    cout << endl;
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printListRangedFor(listOfNums);
    cout << endl;
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    printOtherAuto(listOfNums);
    cout << endl;
    cout << "=======\n";

    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    cout << *myFind(listOfNums,1) << " is found!" << endl;
    if(myFind(listOfNums,420) == listOfNums.end()){
        cout << "420 isn't found!" << endl;
    }
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    cout << "Sorry :'( No C++14" << endl;
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    cout << *find(listOfNums.begin(),listOfNums.end(), 1) << " was found is list!" << endl;
    cout << *find(v.begin(),v.end(), 1) << " was found in vector!" << endl;
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    cout << *find_if(listOfNums.begin(), listOfNums.end(), isEven) << endl;
    cout << *find_if(v.begin(), v.end(), isEven) << endl;
    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    cout << *find_if(listOfNums.begin(), listOfNums.end(), findEven()) << endl;
    cout << "=======\n";

    // 17. Lambda
    cout << "Task 17:\n";
    cout << *find_if(listOfNums.begin(), listOfNums.end(),[](int n){return n%2==0;}) << endl;
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int arr[4];
    copy(listOfNums.begin(), listOfNums.end(),arr);
    for(int n: arr){
        cout << n << " ";
    }
    cout << endl;
    cout << *find(arr,arr, 1) << " was found in vector!" << endl;
    cout << *find_if(arr, arr+4, findEven()) << endl;
    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    cout << *ourFind(listOfNums.begin(),listOfNums.end(),1) << endl;
    cout << "=======\n";

    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    cout << *ourFind(listOfNums.begin(),listOfNums.end(),1) << endl;
    cout << *ourFind(v.begin(),v.end(),1) << endl;
    cout << "=======\n";

    //
    // Associative collections
    //

    ifstream ifs("pooh-nopunc.txt");
    if (!ifs){
        cout << "File does not exist!" << endl;
    }else{
        cout << "File located" << endl;
    }
    // 21. Using a vector of strings, print a line showing
    cout << "Task 21:\n";
    vector<string> collect;
    string word;
    while(ifs>>word){
        if(!foundInVector(collect,word)){
            collect.push_back(word);
        }
    }
    cout << collect.size() << " is the # of unique words in vector!\n";
//    for(const string& w: collect){
//        cout << w << " ";
//    }
    ifs.close();
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    set<string> wordSet;
    ifstream ifs2("pooh-nopunc.txt");
    while(ifs2>>word){
        wordSet.insert(word);
    }
    cout << wordSet.size() << " is the # of unique words in the set!\n";
//    for(const string& w: wordSet){
//        cout << w << " ";
//    }
    ifs2.close();
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string, vector<int>> wordMap;
    int counter = 1;
    ifstream ifs3("pooh-nopunc.txt");
    while(ifs3>>word){
        wordMap[word].push_back(counter);
        counter++;
    }
    cout << wordMap.size() << " is the # of unique words in the set!\n";
    for(const auto& i:wordMap){
        cout << i.first << ": ";
        for(int position: i.second){
            cout << position << " ";
        }
        cout << endl;
    }
    cout << "=======\n";
}
