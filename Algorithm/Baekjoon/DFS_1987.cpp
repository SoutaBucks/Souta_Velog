#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;
using std::string;

vector<vector<char>> board;
vector<int> visitedAlphabet(26, 0);

int R, C, answer = -1;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

/* 초기 입력값 처리 함수
 */
void initialInput() {
    string tempStr;
    cin >> R >> C;

    for(int i = 0; i < R; i++) {
        cin >> tempStr;
        vector<char> tempBoard;

        for(char & c : tempStr)
            tempBoard.push_back(c);

        board.push_back(tempBoard);
    }
}

// 다음 위치의 x, y가 범위 안에 존재하는지 확인하는 함수
bool inBound(const int & x, const int & y) {
    return (0 <= x) and (x < C) and (0 <= y) and (y < R);
}
// 알파벳을 숫자로 바꾸는 함수
int alphabetToNumber(char c) {
    return c - 'A';
}
// 이미 방문한 알파벳인지 확인하는 함수
bool alreadyVisitAlphabet(char c) {
    return visitedAlphabet[alphabetToNumber(c)];
}

// DFS를 이용해 해결
void dfs(int x, int y, int length) {
    visitedAlphabet[alphabetToNumber(board[y][x])] = 1;

    for(int i = 0; i < 4; i++) {
        int nextX = x + dx[i], nextY = y + dy[i];

        // 해당 지점이 존재하지 않거나, 이미 해당 알파벳을 거쳤다면 안된다
        if(not inBound(nextX, nextY) or
        alreadyVisitAlphabet(board[nextY][nextX])) continue;

        dfs(nextX, nextY, length + 1);
    }

    answer = max(answer, length);
    visitedAlphabet[alphabetToNumber(board[y][x])] = 0;
}

void solve() {
    dfs(0, 0, 1);
    cout << answer << endl;
}

int main() {
    initialInput();
    //showArea();
    solve();

    return 0;
}