#include <iostream>
#include <vector>
#include <queue>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::queue;
using std::string;
using std::min;

vector<vector<int>> board, visited, count;
queue<vector<int>> q;

int N, M;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int ctoi(char c) {
  return c - '0';
}

void initialInput() {
  cin >> N >> M;

  string str;

  for(int i = 0; i < N; i++) {
    vector<int> tempBoard, tempVisit;
    cin >> str;
    for(char n : str) {
      tempBoard.push_back(ctoi(n));
      tempVisit.push_back(0);
    }
    board.push_back(tempBoard);
    visited.push_back(tempVisit);
    count.push_back(tempVisit);
  }
}

bool inBound(int x, int y) {
  return (0 <= x) and (x < M) and (0 <= y) and (y < N);
}

bool canBreakWall(int c) {
  return c == 0;
}

bool isRoad(int x, int y) {
  return board[y][x] == 0;
}

bool isWall(int x, int y) {
  return board[y][x] == 1;
}

bool canGo(int x, int y, int c) {
  return inBound(x, y) and (isRoad(x, y) or (isWall(x, y) and canBreakWall(c)));
}

bool arriveFinish(int x, int y) {
  return (x == (M - 1)) and (y == (N - 1));
}

bool canGoShorter(int hereX, int hereY, int nextX, int nextY) {
  return count[nextY][nextX] > count[hereY][hereX] + 1;
}

void bfs(int startX, int startY) {
  q.push({startX, startY, 0});
  visited[startY][startX] = 1;
  count[startY][startX] = 1;


  while(not q.empty()) {
    int hereX = q.front()[0], hereY = q.front()[1], broke = q.front()[2];

    for(int i = 0; i < 4; i++) {
      int nextX = hereX + dx[i], nextY = hereY + dy[i];

      if(canGo(nextX, nextY, broke)) {
        if(not visited[nextY][nextX] or canGoShorter(hereX, hereY, nextX, nextY)) {
          visited[nextY][nextX] = 1;
          count[nextY][nextX] = count[hereY][hereX] + 1;
          q.push({nextX, nextY, isWall(nextX, nextY) ? broke + 1 : broke});
        }
      }
    }
    q.pop();
  }
}
/*
void bfs() {
  q.emplace(0, 0);

  while(not q.empty()) {
    int hereX = q.front().first, hereY = q.front().second;
    bool blocked = true;

    if(arriveFinish(hereX, hereY))  {
      q.pop();
      continue;
    }

    for(int i = 0; i < 4; i++) {
      int nextX = hereX + dx[i], nextY = hereY + dy[i];

      if(canGo(nextX, nextY)) {
        if(not visited[nextY][nextX] or canGoShorter(hereX, hereY, nextX, nextY)) {
          visited[nextY][nextX] = 1;
          count[nextY][nextX] = count[hereY][hereX] + 1;
          q.emplace(nextX, nextY);
          blocked = false;
        }
      }
    }

    q.pop();
  }

  //cout << "Um : " << count[N - 1][M - 1] << endl;
}


void getWallsPoint() {
  for(int y = 0; y < N; y++) {
    for(int x = 0; x < M; x++) {
      if(board[y][x] == 1)
        walls.emplace_back(x, y);
    }
  }
}

void initializeVisited() {
  for(auto & row : visited) {
    for(auto & n : row)
      n = 0;
  }
  visited[0][0] = 1;
}


void allBfs() {
  if (walls.empty()) {
    bfs();
    answer = count[N-1][M-1];
  }

  for(auto point : walls) {
    int wallX = point.first, wallY = point.second;
    board[wallY][wallX] = 0;
    bfs();
    board[wallY][wallX] = 1;
    if(count[N-1][M-1] != 0)
      answer = min(answer, count[N - 1][M - 1]);
    //initializeVisitedAndCount();
    initializeVisited();
  }

}

void solve() {
  getWallsPoint();
  allBfs();
  if(answer == 987654321) cout << -1 << endl;
  else                    cout << answer << endl;
}
*/

void initializeVisitedAndCount() {

  for(int y = 0; y < N; y++) {
    for(int x = 0; x < M; x++) {
      visited[y][x] = 0;
      count[y][x] = 0;
    }
  }
}


void solve() {
  int answerFirst, answerSecond;
  bfs(0, 0);
  answerFirst = count[N-1][M-1];
  initializeVisitedAndCount();
  bfs(M - 1, N - 1);
  answerSecond = count[0][0];

  if(answerFirst == 0 and answerSecond == 0) cout << -1 << endl;
  else if(answerFirst == 0)  cout << answerSecond << endl;
  else if(answerSecond == 0)  cout << answerFirst << endl;
  else                    cout << min(answerFirst, answerSecond) << endl;
}

int main() {
  initialInput();
  solve();

  return 0;
}