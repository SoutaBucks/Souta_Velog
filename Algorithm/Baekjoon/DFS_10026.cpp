#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

vector<vector<int>> colorWeakArea;
vector<vector<int>> notColorWeakArea;
vector<vector<int>> visitedArea;

int N, colorWeak = 0, notColorWeak = 0;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

// 각 색을 숫자로 변환
// Red = 1, Blue = 2, Green = 3
int colorToNum(char & c) {
    int result = -1;

    switch (c) {
        case 'R':
            result = 1;
            break;
        case 'B':
            result = 2;
            break;
        case 'G':
            result = 3;
            break;
        default:
            break;
    }

    return result;
}

/* 초기 입력값 처리 함수
 * 색약이 보는 색들과
 * 색약이 아닌 사람들이 보는 색들을
 * 각각 만들었다
 */
void initialInput() {
    string tempstr;
    cin >> N;

    for(int i = 0; i < N; i++) {
        vector<int> tempColorWeakArea, tempNotColorWeakArea, tempVisit;
        cin >> tempstr;
        for(char & c : tempstr) {

            tempColorWeakArea.push_back(c == 'G' ? 1 : colorToNum(c));
            tempNotColorWeakArea.push_back(colorToNum(c));

            tempVisit.push_back(0);
        }
        visitedArea.push_back(tempVisit);
        colorWeakArea.push_back(tempColorWeakArea);
        notColorWeakArea.push_back(tempNotColorWeakArea);
    }
}

// visitedArea를 초기화 하는 함수
void initialVisit() {
    for(auto & row : visitedArea) {
        for(auto & n : row)
            n = 0;
    }
}

// 이미 방문 됐는지 여부 확인 함수
bool isVisited(const int & here) {
    return here == 1;
}

// 다음 위치의 x, y가 범위 안에 존재하는지 확인하는 함수
bool inBound(const int & x, const int & y) {
    return (0 <= x) and (x < N) and (0 <= y) and (y < N);
}

// DFS를 이용해 해결
void dfs(int x, int y, bool isColorWeak) {
    visitedArea[y][x] = 1;

    for(int i = 0; i < 4; i++) {
        int nextX = x + dx[i], nextY = y + dy[i];
        // 범위 확인
        if(not inBound(nextX, nextY)) continue;

        // 각 시점에 따라 보는 색이 다르다
        int here = (isColorWeak ? colorWeakArea[y][x] : notColorWeakArea[y][x]);
        int next = (isColorWeak ? colorWeakArea[nextY][nextX] : notColorWeakArea[nextY][nextX]);

        // 아직 방문하지 않은 구역이 있다면 방문하기
        if(not isVisited(visitedArea[nextY][nextX]) and (here == next))
            dfs(nextX, nextY, isColorWeak);

    }
}

// 모든 구역을 방문하기 위해 DFS로 전부 방문하기
void dfsAll(bool isColorWeak) {
    for(int y = 0; y < N; y++) {
        for(int x = 0; x < N; x++) {
            if(not isVisited(visitedArea[y][x])) {
                isColorWeak ? colorWeak++ : notColorWeak++;
                dfs(x, y, isColorWeak);
            }
        }
    }
}

void solve() {
    dfsAll(true);   // 색약이 봤을 때 구역 수
    initialVisit();
    dfsAll(false);   // 색약이 아닌 사람이 봤을 때 구역 수

    cout << notColorWeak << " " << colorWeak << endl;
}


void showArea(bool isColorWeak) {
    for(auto & row : (isColorWeak ? colorWeakArea : notColorWeakArea)) {
        for(auto & num : row)
            cout << num << " ";
        cout << endl;
    }
}

int main() {
    initialInput();
    /*
    showArea(0);
    cout << "----------------------\n";
    showArea(1);
    */
    solve();

    return 0;
}