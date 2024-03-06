#include <iostream>
#include <vector>
#include <string>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::ios;
using std::string;
using std::queue;
using std::make_pair;
using std::pair;

int N, M;
vector<vector<int>> board, takeCount;
vector<vector<bool>> visited;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};


int charToInt(char c) {
  return c - '0';
}

void makeBoard() {
  string tempString;

  cin >> N >> M;
  for(int i = 0; i < N; i++) {
    vector<int> tempBoard, tempCount;
    vector<bool> tempVisited;
    cin >> tempString;

    for(char & c : tempString) {
      tempBoard.push_back(charToInt(c));
      tempVisited.push_back(false);
      tempCount.push_back(0);
    }

    visited.push_back(tempVisited);
    board.push_back(tempBoard);
    takeCount.push_back(tempCount);
  }
}

// 다음 위치로 갈 수 있는지 확인하는 함수
bool canGo(int x, int y) {
  return (x >= 0 && x < M) && (y >= 0 && y < N) && (board[y][x] == 1 && not visited[y][x]);
}

// bfs를 통해 확인
void bfs(pair<int, int> start) {
  queue<pair<int, int>> nextToGo;
  int startX = start.first, startY = start.second;

  // Queue에 현재 위치를 넣는다
  nextToGo.push(start);
  visited[startY][startX] = true;
  takeCount[startY][startX] = 1;  // 처음 위치도 1로 시작

  while(not nextToGo.empty()) {
    // 현재 위치를 Queue에서 얻어온다
    pair<int, int> herePair = nextToGo.front();
    int hereX = herePair.first, hereY = herePair.second;
    nextToGo.pop();

    // 다음 위치를 Queue에 넣고 확인한다
    for(int i = 0; i < 4; i++) {
      int nextX = hereX + dx[i], nextY = hereY + dy[i];
      if(not canGo(nextX, nextY)) continue;
      nextToGo.push(make_pair(nextX, nextY));
      visited[nextY][nextX] = true;
      // 어짜피 가장 짧은 거리는 제일 먼저 bfs의 Queue내에서 제일 먼저 도착할 것이다.
      takeCount[nextY][nextX] = takeCount[hereY][hereX] + 1;
    }
  }

}

void solve() {
  makeBoard();

  bfs(make_pair(0, 0));

  cout << takeCount[N - 1][M - 1];
}

int main() {
  /* 아래 3문장은
   * 출력과 입력을 빠르게 하기 위해서 적는 문장이다.
   * */
  cin.tie(NULL);
  cout.tie(NULL);
  ios::sync_with_stdio(false);

  solve();

  return 0;
}
