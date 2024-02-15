#include <iostream>
#include <vector>

using namespace std;

int ROW = 0, COL = 0;
vector<vector<char>> board;

void makeBoard() {
    cin >> ROW >> COL;
    string rowString;
    for(int i = 0; i < ROW; i++) {
        cin >> rowString;
        vector<char> tempVector;
        for(char & j : rowString)
            tempVector.push_back(j);
        board.push_back(tempVector);
    }
}

void showBoard() {
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isOddNum(int num) {
    return num % 2 != 0;
}

bool isWhite(char c) {
    return c == 'W';
}

bool shouldChange(int nextX, int nextY, char firstCharacter) {
    if(firstCharacter == 'W')
        return (!isOddNum(nextX + nextY) && !isWhite(board[nextY][nextX])) || (isOddNum(nextX + nextY) && isWhite(board[nextY][nextX]));
    else
        return (!isOddNum(nextX + nextY) && isWhite(board[nextY][nextX])) || (isOddNum(nextX + nextY) && !isWhite(board[nextY][nextX]));
}


int reviewBoard(int firstX, int firstY, char firstCharacter) {
    int result = 0, nextX = 0, nextY = 0;

    for(int y = 0; y < 8; y++) {
        nextY = firstY + y;
        for(int x = 0; x < 8; x++) {
            nextX = firstX + x;
            if(shouldChange(nextX, nextY, firstCharacter))
                result++;
        }
    }

    return result;
}


int solve() {
    int whiteResult = 987654321, blackResult = 987654321;

    // whiteResult
    for(int y = 0; y < ROW - 7; y++) {
        for(int x = 0; x < COL - 7; x++) {
             whiteResult = min(whiteResult, reviewBoard(x, y, 'W'));
        }
    }

    // blackResult
    for(int y = 0; y < ROW - 7; y++) {
        for(int x = 0; x < COL - 7; x++) {
            blackResult = min(blackResult, reviewBoard(x, y, 'B'));
        }
    }
    return min(whiteResult, blackResult);
}

int main() {
    makeBoard();
    cout << solve() << endl;
    //showBoard();
}
