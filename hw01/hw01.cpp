/*
    hw01: Basic C++
    Michael Li
    Purpose: To decrypt a cyphertext created by Caesar Cypher
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
    Purpose: Given a character and the units to cycle backwards, the function returns the decrypted character.
    Parameters: char character - character to cycle back
                int cycleUnit - units to cycle back
    Return Value: char repChar - decrypted character
*/
char findDecryptChar(const char& character,const int& cycleUnit){
    //decrypt if the character is a lowercase letter
    if (character >= 'a' and character <= 'z'){
        char repChar = character;
        repChar-=cycleUnit;
        //if out of range, wrap around.
        if (repChar < 'a'){
            repChar+=26;
        }
        return repChar;
    }else{
        return character;
    }
}

/*
    Purpose: Given a string, change each character in that string to the decrypted character
    Parameters: string str - string to modify
                int cycleUnit - units to cycle back for each character in string
    Return Value: void - modifies original string
*/
void changeString(string& str,const int& cycleUnit){
    //loops through string to change each character to its deciphered character
    for(int i = 0; i < int(str.size()); ++i){
        str[i] = findDecryptChar(str[i],cycleUnit);
    }
}

int main()
{
    //open file
    ifstream ifs("encrypted.txt");
    //check if able to open file
    if (!ifs){
        cout << "failed to open file" << endl;
        exit(1);
    }else{
        //initialize necessary variables
        string line;
        vector<string> lineStorage;
        int cycle;

        //get steps to cycle
        ifs >> cycle;

        //read file, decipher and add each line to fileStorage
        while (getline(ifs,line)){
            changeString(line,cycle);
            lineStorage.push_back(line);
        }

        //go through lineStorage backwards and read the lines
        for (size_t index = lineStorage.size(); index > 0; --index){
            cout << lineStorage[index-1] << endl;
        }

        //close file
        ifs.close();
    }

    return 0;
}


