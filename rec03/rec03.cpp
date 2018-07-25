/*
    Michael Li
    rec03: Minesweeper
*/

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Minesweeper{
public:
    Minesweeper(int row, int col): row(row), col(col){
        makeBoard(row,col);
        setupBoard();
    }

    bool done(){
        int vis;
        int totalVis;
        totalVis = (row * col) - bombs;
        int rowCount;
        int colCount;
        rowCount = mineBoard.size();
        colCount = mineBoard[0].length();
        vis = 0;
        for (int col = 0; col < colCount; ++col){
            for (int row = 0; row < rowCount; ++row){
                if (visibleBoard[row][col] == 'T'){
                    vis+=1;
                }
            }
        }

        if (vis == totalVis){
            return true;
        }else{
            return false;
        }
    }

    bool validRow(int inputRow)const {
        if (inputRow > 0 and inputRow <= row+1){
            return true;
        }else{
            return false;
        }
    }

    bool validCol(int inputCol)const{
        if (inputCol > 0 and inputCol <= col+1){
            return true;
        }else{
            return false;
        }
    }

    char num(int number)const{
        if(number == 0){
            return '0';
        }

        if(number == 1){
            return '1';
        }

        if(number == 2){
            return '2';
        }

        if(number == 3){
            return '3';
        }

        if(number == 4){
            return '4';
        }

        if(number == 5){
            return '5';
        }

        if(number == 6){
            return '6';
        }

        if(number == 7){
            return '7';
        }

        if(number == 8){
            return '8';
        }
    }

    void makeMove(int row, int col){
        if(mineBoard[row][col] == '*' or visibleBoard[row][col] == 'T'){
            return;
        }

        visibleBoard[row][col] = 'T';
        int bombCount = 0;
        for(int r = -1; r <= 1; ++r){
            for (int c = -1; c <= 1; ++c){
                if (r == 0 and c == 0){
                    continue;
                }
                if (mineBoard[row+r][col+c] == 'B'){
                    bombCount+=1;
                }
            }
        }
        cout << bombCount << "is the bomb count" << endl;

        mineBoard[row][col] = bombCount;
        if (bombCount != 0){
            mineBoard[row][col] = num(bombCount);
        }else{
        //if no bombs detected
            mineBoard[row][col] = '0';
            for(int r = -1; r <= 1; ++r){
                for (int c = -1; c <= 1; ++c){
                    if (r == 0 and c == 0){
                        continue;
                    }
                    makeMove(row+r,col+c);
                }
            }
        }

    }

    bool play(int row, int col){
        if (mineBoard[row][col] == 'B'){
            return false;
        }else{
            makeMove(row,col);
        }
        display(false);
        return true;
    }

    bool isVisible(int row, int col) const{
        if (visibleBoard[row][col] == 'T' or visibleBoard[row][col] == '*'){
            return true;
        }else{
            return false;
        }
    }

    void testDisplay() const{
        cout << "This is visibleBoard" << endl;
        int rowCount;
        int colCount;
        rowCount = mineBoard.size();
        colCount = mineBoard[0].length();
        for (int col = 0; col < colCount; ++col){
            for (int row = 0; row < rowCount; ++row){
                cout << visibleBoard[row][col];
            }
            cout << endl;
        }
    }
    void display(const bool& showAll = false) const{
        int rowCount;
        int colCount;
        rowCount = mineBoard.size();
        colCount = mineBoard[0].length();

        if(showAll == true){
            for (int col = 0; col < colCount; ++col){
                for (int row = 0; row < rowCount; ++row){
                    cout << mineBoard[row][col];
                }
                cout << endl;
            }
        }else{
            for (int col = 0; col < colCount; ++col){
                for (int row = 0; row < rowCount; ++row){
                    if(isVisible(row,col)){
                        cout << mineBoard[row][col];
                    }else{
                        cout << ' ';
                    }
                }
                cout << endl;
            }
        }
    }
private:
    int row;
    int col;
    vector<string> visibleBoard;
    vector<string> mineBoard;
    int bombs;

    void makeBoard(int row, int col){
        string leftRightBorder ="**";
        for (int c = 0; c < col; ++c){
            leftRightBorder+= "*";
        }
        mineBoard.push_back(leftRightBorder);

        string rowString = "*";
        for (int c = 0; c < col; ++c){
            rowString+= " ";
        }
        rowString += "*";
        for (int r = 0; r < row; ++r){
            mineBoard.push_back(rowString);
        }
        mineBoard.push_back(leftRightBorder);

        visibleBoard = mineBoard;
    }

    void setupBoard(){
        srand(time(NULL));
        for(int c = 1; c < col + 1; ++c){
            for(int r = 1; r < row + 1; ++r){
                if(rand()%100 < 10){
                    mineBoard[c][r] = 'B';
                    bombs+=1;
                }
            }
        }
    }

};


int main() {
    Minesweeper sweeper = Minesweeper(10,10);
    // Continue until only invisible cells are bombs
    while (!sweeper.done()) {
        sweeper.display(false); // display board without bombs

        int row_sel = -1, col_sel = -1;
        while (row_sel == -1) {
            // Get a valid move
            int r, c;
            cout << "row? ";
            cin >> r;
            if (!sweeper.validRow(r)) {
                cout << "Row out of bounds\n";
                continue;
            }
            cout << "col? ";
            cin >> c;
            if (!sweeper.validRow(c)) {
                cout << "Column out of bounds\n";
                continue;
            }
            if (sweeper.isVisible(r,c)) {
                cout << "Square already visible\n";
                continue;
            }
            row_sel = r;
            col_sel = c;
        }
        // Set selected square to be visible. May effect other cells.
        if (!sweeper.play(row_sel,col_sel)) {
            cout << "Sorry, you died..\n";
            sweeper.display(true); // Final board with bombs shown
            exit(0);
        }
    }
    // Ah! All invisible cells are bombs, so you won!
    cout << "You won!!!!\n";
    sweeper.display(true); // Final board with bombs shown
}
