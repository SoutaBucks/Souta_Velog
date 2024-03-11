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
using std::max;
using std::copy;

int N, M, answer = -1;
vector<vector<int>> originalBoard, newBoard, newBoard2; // 원래보드, 벽을 세울 보드, 벽 다 세우고 초기화 할 보드
vector<pair<int, int>> virusPositions;                  // 바이러스 위치
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

bool isEmpty(int here) {  return here == 0; }
bool isWall(int here)  {  return here == 1; }
bool isVirus(int here) {  return here == 2; }

// 다음 위치로 갈 수 있는지 확인하는 함수
bool canGo(int x, int y) {
  return (x >= 0 && x < M) && (y >= 0 && y < N) && (newBoard[y][x] == 0);
}

// 보드 만드는 함수
void makeBoard() {
  int n;

  cin >> N >> M;
  for(int i = 0; i < N; i++) {
    vector<int> tempBoard;

    for(int j = 0; j < M; j++) {
      cin >> n;
      tempBoard.push_back(n);

      if(n == 2)
        virusPositions.push_back(make_pair(j, i));
    }

    originalBoard.push_back(tempBoard);
    newBoard.push_back(tempBoard);
    newBoard2.push_back(tempBoard);
  }
}

// 벽을 다 세우고 보드를 바이러스 퍼지기 전으로 초기화 하는 함수
void initalizeBoard() {
  copy(newBoard2.begin(), newBoard2.end(), newBoard.begin());
}

// bfs를 통해 확인
void bfs(pair<int, int> start) {
  queue<pair<int, int>> nextToGo;
  // Queue에 현재 위치를 넣는다
  nextToGo.push(start);

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
      newBoard[nextY][nextX] = 2; // 바이러스를 점점 퍼트리자
    }
  }

}

// 안전 영역을 구하는 함수
int getSafeArea() {
  int result = 0;

  for(int y = 0; y < N; y++) {
    for(int x = 0; x < M; x++) {
      if(isEmpty(newBoard[y][x]))
        result++;
    }
  }

  return result;
}

// 보드 확인 함수
void showBoard() {
  cout << "------------------------------\n";
  for(int y = 0; y < N; y++) {
    for(int x = 0; x < M; x++)
      cout << newBoard[y][x] << " ";
    cout << "\n";
  }
}

// 재귀 함수를 이용하여 벽을 놓는다
void putWalls(int wallCount, int startX, int startY) {

  // 벽을 3개를 다 놓았다면 bfs를 통해 세균을 증식시키자
  if (wallCount == 3) {
    //showBoard();

    for(auto & here : virusPositions)
      bfs(here);
    answer = max(answer, getSafeArea());
    initalizeBoard();
    return;
  }

  // 시작하는 Y좌표가 판의 범위를 넘어섰다면 벽을 놓을 수 없다는 의미
  if(startY == -1)  return;

  int nextX, nextY;

  for(int y = startY; y < N; y++) {
    for(int x = startX; x < M; x++) {
      if(isEmpty(originalBoard[y][x])) {
        newBoard[y][x] = newBoard2[y][x] = 1;

        nextX = x + 1;
        nextY = y;

        // X 위치가 끝이면 한 칸 밑으로 내려 처음부터 벽을 놓자
        if(nextX == M) {
          nextX = 0;
          nextY = y + 1;
        }

        // Y 위치가 끝에 다다랐다는 것은 더 이상 벽을 놓을 곳이 없다는 의미
        if(nextY == N) nextY = -1;

        putWalls(wallCount + 1, nextX, nextY);
        newBoard[y][x] = newBoard2[y][x] = 0;
      }
    }
    startX = 0;   // 다음 줄부터는 X좌표 처음부터 벽을 놓자
  }

}

void solve() {
  makeBoard();
  putWalls(0, 0, 0);
  cout << answer;
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
