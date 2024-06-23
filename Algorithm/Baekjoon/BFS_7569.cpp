#include <iostream>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::abs;
using std::vector;
using std::queue;

vector<vector<int>> tomato;
vector<vector<int>> visited;
queue<vector<int>> q;

int M, N, H, answer = 0;
// 앞, 오른쪽, 뒤, 왼쪽, 위, 아래
int dx[] = {0, 1, 0, -1, 0, 0};
int dy[] = {1, 0, -1, 0, H, -H};

// 초기 입력값 처리 함수

void initialInput() {
  cin >> M >> N >> H;
  dy[4] = N;
  dy[5] = -N;

  int n;

  for(int i = 0; i < N * H; i++) {
    vector<int> tempTomato, visitTemp;
    for(int j = 0; j < M; j++) {
      cin >> n;
      tempTomato.push_back(n);
      visitTemp.push_back(0);
    }
    tomato.push_back(tempTomato);
    visited.push_back(visitTemp);
  }
}

bool isAllGrown() {

  for(int i = 0; i < N * H; i++) {
    for(int j = 0; j < M; j++) {
      if(tomato[i][j] == 0)
        return false;
    }
  }

  return true;
}

// 다음층으로 멋대로 넘어가는 것을 확인하는 함수
bool goNextFloor(int hereY, int nextY) {
  return (abs(nextY - hereY) == 1) and (nextY / N != hereY / N);
}

bool isInBound(int x, int hereY, int nextY) {
  return (0 <= x) and (x < M) and (0 <= nextY) and (nextY < H * N) and not goNextFloor(hereY, nextY);
}

bool canPutTomato(int x, int y) {
  return tomato[y][x] == 0 and not visited[y][x];
}

void showTomato() {
  for(int y = 0; y < N * H; y++) {
    for(int x = 0; x < M; x++) {
      cout << tomato[y][x] << " ";
    }
    cout << endl;
  }
  cout << "---------------------" << endl;
}

// 하루가 지났음을 확인하는 함수
bool oneDayPass(int x, int y) {
  return (x == -1) and (y == -1);
}

void bfs() {

  while(not q.empty()) {
    vector<int> here = q.front();
    int hereX = here[0], hereY = here[1];

    if(oneDayPass(hereX, hereY)) {
      //showTomato();
      q.pop();
      if(q.empty()) break;
      answer++;
      q.push({-1, -1});
      continue;
    }


    for (int i = 0; i < 6; i++) {
      int nextX = hereX + dx[i], nextY = hereY + dy[i];
      if (isInBound(nextX, hereY, nextY) and canPutTomato(nextX, nextY)) {
        visited[nextY][nextX] = 1;
        tomato[nextY][nextX] = 1;
        q.push({nextX, nextY});
      }
    }

    q.pop();
  }
}

void findAllTomatoFirst() {
  for(int y = 0; y < H * N; y++) {
    for(int x = 0; x < M; x++) {
      if(tomato[y][x] == 1) {
        q.push({x, y});
        visited[y][x] = 1;
      }
    }
  }
  q.push({-1, -1});
  bfs();
}


void solve() {
  bool needToShowAnswer = true;

  if(isAllGrown()) {
    cout << "0" << endl;
    needToShowAnswer = false;
  }

  findAllTomatoFirst();

  if(not isAllGrown()) {
    cout << "-1" << endl;
    needToShowAnswer = false;
  }

  if(needToShowAnswer)
    cout << answer << endl;
}

int main() {
  initialInput();
  solve();
  //showTomato();

  return 0;
}



/*
vector<vector<vector<int>>> tomato;
vector<vector<vector<int>>> visited;
queue<vector<int>> q;

int M, N, H, answer = 0;
// 앞, 오른쪽, 뒤, 왼쪽, 위, 아래
int dx[] = {0, 1, 0, -1, 0, 0};
int dy[] = {1, 0, -1, 0, 0, 0};
int dz[] = {0, 0, 0, 0, 1, -1};

/* 초기 입력값 처리 함수

void initialInput() {
  cin >> M >> N >> H;

  for(int i = 0; i < H; i++) {
    vector<vector<int>> temp1;
    vector<vector<int>> visitTemp_1;
    for(int j = 0; j < N; j++) {
      vector<int> temp2;
      vector<int> visitTemp_2;
      int n;
      for(int k = 0; k < M; k++) {
        cin >> n;
        temp2.push_back(n);
        visitTemp_2.push_back(0);
      }
      temp1.push_back(temp2);
      visitTemp_1.push_back(visitTemp_2);
    }
    tomato.push_back(temp1);
    visited.push_back(visitTemp_1);
  }

}

bool isAllGrown() {

  for(int i = 0; i < H; i++) {
    for(int j = 0; j < N; j++) {
      for(int k = 0; k < M; k++) {
        if(tomato[i][j][k] == 0)
          return false;
      }
    }
  }

  return true;
}

bool isInBound(int x, int y, int z) {
  return (0 <= x) and (x < M) and (0 <= y) and (y < N) and (0 <= z) and (z < H);
}

bool canPutTomato(int x, int y, int z) {
  return tomato[z][y][x] == 0 and not visited[z][y][x];
}

void showTomato() {
  for(int i = 0; i < H; i++) {
    for(int j = 0; j < N; j++) {
      for(int k = 0; k < M; k++)
        cout << tomato[i][j][k] << " ";
      cout << endl;
    }
    cout << "------------------------------" << endl;
  }
}

// 하루가 지났음을 확인하는 함수
bool oneDayPass(int x, int y, int z) {
  return (x == -1) and (y == -1) and (z == -1);
}

void bfs(int x, int y, int z) {
  q.push({x, y, z});
  q.push({-1, -1, -1}); // 하루 구분용

  while(not q.empty()) {
    vector<int> here = q.front();
    int hereX = here[0], hereY = here[1], hereZ = here[2];

    if(oneDayPass(hereX, hereY, hereZ)) {
      q.pop();
      if(q.empty()) break;
      answer++;
      q.push({-1, -1, -1});
      continue;
    }
    visited[hereZ][hereY][hereX] = 1;
    tomato[hereZ][hereY][hereX] = 1;

    for (int i = 0; i < 6; i++) {
      int nextX = hereX + dx[i], nextY = hereY + dy[i], nextZ = hereZ + dz[i];
      if (isInBound(nextX, nextY, nextZ) and canPutTomato(nextX, nextY, nextZ))
        q.push({nextX, nextY, nextZ});
    }

    q.pop();
  }
}

void allBfs() {
  for(int i = 0; i < H; i++) {
    for(int j = 0; j < N; j++) {
      for(int k = 0; k < M; k++) {
        if(tomato[i][j][k] == 1 and not visited[i][j][k])
          bfs(k, j, i);
      }
    }
  }
}


void solve() {
  bool needToShowAnswer = true;

  if(isAllGrown()) {
    cout << "0" << endl;
    needToShowAnswer = false;
  }

  allBfs();

  if(not isAllGrown()) {
    cout << "-1" << endl;
    needToShowAnswer = false;
  }

  if(needToShowAnswer)
    cout << answer << endl;
}

int main() {
  initialInput();
  solve();
  //showTomato();

  return 0;
}*/