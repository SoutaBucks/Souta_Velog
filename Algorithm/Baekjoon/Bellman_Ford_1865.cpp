
#include <iostream>
#include <vector>

using std::cin, std::cout, std::endl, std::vector;

/* TC - 테스트 케이스 개수
 * N - 지점 수
 * M - 도로 수
 * W - 웜홀 수
 * S - 시작 지점
 * E - 도착 지점
 * T - 도로를 통해 이동하는데 걸리는 시간
 * */

const int INF = 987654321;
int TC, N, M, W, S, E, T;

vector<long> upper;
vector<vector<int>> board;

void showUpper() {
  for(int i = 1; i <= N; i++) {
    cout << upper[i] << " ";
  }
  cout << endl;
}

void initialInput() {
  upper = vector<long> (501, INF);
  board.clear();
  cin >> N >> M >> W;
  // 도로 정보 받기
  for(int j = 0; j < M; j++) {
    cin >> S >> E >> T;
    board.push_back({S, E, T});
    board.push_back({E, S, T});
  }
  // 웜홀 정보 받기
  for(int k = 0; k < W; k++) {
    cin >> S >> E >> T;
    board.push_back({S, E, -T});
  }
}


bool bellmanFord(int start) {
  upper[start] = 0;

  for(int i = 0; i < N; i++) {
    // 모든 도로를 관찰 (모든 간선 확인)
    for(int j = 0; j < M * 2 + W; j++) {
      int from = board[j][0];
      int to = board[j][1];
      int weight = board[j][2];

      /* 예)
       * 서로 연결 되어 있지 않은 섬 2개가 있다.
       * 1번째 섬이 아닌 2번째 섬에서 음수 사이클이 발생할 수 있다.
       * 그럴 경우 아래 코드를 삽입하게 되면 갈 수 없는 섬으로 인식하여 탐색할 수 없게 된다.
       * */
      //if(upper[from] == INF) continue;

      if(upper[to] > upper[from] + weight) {
        upper[to] = upper[from] + weight;

        if(i == N - 1)
          return true;
      }
    }
  }
  return false;
}

void solve(int start) {
  cin >> TC;
  for(int i = 0; i < TC; i++) {
    initialInput();
    bool canBack = bellmanFord(start);
    if(not canBack) cout << "NO" << endl;
    else            cout << "YES" << endl;
    //showUpper();
  }
}

int main() {
  solve(1);
  return 0;
}
