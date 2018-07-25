/*
    Michael Li
    rec02: Structs, Vectors and Functions
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Hydrocarbon{
    string name;
    int carbon;
    int hydrogen;

    Hydrocarbon(const string& name, const int& cCount, const int& hCount){
        this->name = name;
        this->carbon = cCount;
        this->hydrogen = hCount;
    }
};

void printHCarbons(const vector<Hydrocarbon>& hydrocarbons, const int& maxCarbon);
size_t findHCarbon(const vector<Hydrocarbon>& hydrocarbons,const int& cCount,const int& hCount);

int main()
{
    ifstream ifs("hydrocarbon.txt");
    size_t index;
    string name;
    char letter;
    int cNum;
    int hNum;
    int maxCarbon = 0;
    vector<Hydrocarbon> hydrocarbons;

    if(!ifs){
        cout << "cannot open file." << endl;
    }else{
        while(ifs >> name){
            ifs >> letter;
            ifs >> cNum;
            if(cNum > maxCarbon){
                maxCarbon = cNum;
            }
            ifs >> letter;
            ifs >> hNum;

            index = findHCarbon(hydrocarbons,cNum,hNum);
            if(index < hydrocarbons.size()){
                hydrocarbons[index].name += " " + name;
            }else{
                hydrocarbons.push_back(Hydrocarbon(name, cNum, hNum));
            }
        }

        printHCarbons(hydrocarbons, maxCarbon);
        ifs.close();
    }
    return 0;
}

void printHCarbons(const vector<Hydrocarbon>& hydrocarbons, const int& maxCarbon){
    int current = 1;
    while(current <= maxCarbon){
        for (const Hydrocarbon& hc : hydrocarbons){
            if(current ==  hc.carbon){
                cout << 'C' << hc.carbon << 'H' << hc.hydrogen << ' ' << hc.name << endl;
            }
        }
        current+=1;
    }

}
size_t findHCarbon(const vector<Hydrocarbon>& hydrocarbons,const int& cCount,const int& hCount){
    for (size_t i = 0; i < hydrocarbons.size(); ++i){
        if (hydrocarbons[i].carbon == cCount and hydrocarbons[i].hydrogen == hCount){
            return i;
        }
    }
    return hydrocarbons.size();
}
