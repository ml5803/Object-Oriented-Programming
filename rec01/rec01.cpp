/*
    Michael Li
    rec01: C++ Basics
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

 void printVector(const vector<string>& board){
    int rowCount;
    int colCount;
    rowCount = board.size();
    colCount = board[0].length();
    //cout << rowCount << " is the rows " << colCount << " is the col" << endl;

    for (int col = 0; col < colCount; ++col){
        for (int row = 0; row < rowCount; ++row){
            cout << board[row][col];
        }
        cout << endl;
    }
 }

 vector<string> copyBoard(const vector<string>& original){
    vector<string> dup;
    for(const string& col: original){
        dup.push_back(col);
    }

    return dup;
}

vector<string> makeBoard(const string& fileName){
    vector<string> board;
    ifstream ifs(fileName);
    if (!ifs){
        cerr << "can't open file" << endl;
        exit(1);
    }
    string line;
    int width;

    //get first line and length of line
    getline(ifs,line);
    width = line.length();

    for (int i = 0; i < width + 2; ++i){
        board.push_back(" "); //create empty row
    }

    //adds first row
    for (int ch = 0; ch < width + 2; ++ch){
        if(ch == 0 or ch == width + 1){
            board[ch] += " ";
        }else{
            if (string(1,line[ch-1]) == "*"){
                    board[ch] += "*";
            }else{
                    board[ch] += " ";
            }
        }
    }

    //put items in rest of board
    while(getline(ifs,line)){
        for (int ch = 0; ch < width + 2; ++ch){
            if(ch == 0 or ch == width + 1){
                board[ch] += " ";
            }else{
                if (string(1,line[ch-1]) == "*"){
                    board[ch] += "*";
                }else{
                    board[ch] += " ";
                }
            }
        }
    }

    //adds last row
    for (int ch = 0; ch < width + 2; ++ch){
            board[ch] += " ";
    }
    ifs.close();
    return board;
}

bool checkStatus(const vector<string>& board, int row, int col){
    int aliveCount;
    aliveCount = 0;
    for(int colInd = -1; colInd <= 1; ++colInd){
        for(int rowInd = -1; rowInd <=1; ++rowInd){
            if (colInd == 0 and rowInd == 0){
                continue;
            }else{
                if(string(1,board[row+rowInd][col+colInd]) == "*"){
                    aliveCount+=1;
                }
            }
        }
    }

    if (string(1,board[row][col]) == "*" and (aliveCount == 2 or aliveCount == 3)){
        return true;
    }
    else{
        if (string(1,board[row][col]) == " " and aliveCount == 3){
            return true;
        }
    }
    return false;
}

vector<string> nextGeneration(const vector<string>& board){
    vector<string> dup;
    dup = copyBoard(board);

    int rowCount;
    int colCount;

    rowCount = board.size();
    colCount = board[0].length();

    for(int row = 1; row < rowCount-1; ++row){
        for(int col = 1; col < colCount-1; ++col){
            if (checkStatus(board,row,col)){
                dup[row][col] = '*';
            }else{
                dup[row][col] = ' ';
            }
        }
    }

    return dup;
}

int main()
{
    vector<string> board;
    vector<string> dup;
    board = makeBoard("life.txt");
    printVector(board);

    for(int i = 0; i < 10; ++i){
        cout << "Generation : " << i + 1 << endl;
        dup = nextGeneration(board);
        printVector(dup);
        board = dup;
    }

    return 0;
}


