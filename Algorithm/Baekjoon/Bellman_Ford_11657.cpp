#include <iostream>
#include <vector>

/*
 * N - 도시의 개수
 * M - 버스 노선 개수
 * A - 시작 도시
 * B - 도착 도시
 * C - 버스 이동 시간
 * C > 0 일반, C = 0 순간 이동, C < 0 과거로 시간을 돌아가는 경우
 * */

using std::cin, std::cout, std::endl, std::vector, std::pair, std::make_pair;

const int INF = 987654321;
vector<long> upper(501, INF);
vector<vector<int>> board;
int N, M, A, B, C;

void initialInput() {
  cin >> N >> M;
  for(int i = 0; i < M; i++) {
    cin >> A >> B >> C;
    board.push_back({A, B, C});
  }
}

void showBoard() {
  for(int i = 0; i < N; i++) {
    for(auto & e : board[i])
      cout << e << ", ";
    cout << endl;
  }
}

// 음수 사이클이 존재하면 true 반환
bool bellmanFord(int start) {
  upper[start] = 0;

  // 과정을 N번 반복한다 (음수 사이클 존재를 확인하기 위해 N-1이 아니라 N번)
  for(int i = 1; i <= N; i++) {
    // 모든 간선을 확인한다
    for(int j = 0; j < M; j++) {
      int from = board[j][0];
      int end = board[j][1];
      int weight = board[j][2];

      // 시작점이 INF이라면 여기까지 가는 최단 경로를 찾지 못했으니까 무시
      if(upper[from] == INF) continue;

      // 새로운 최단 거리를 발견한다면 갱신하자
      if(upper[end] > upper[from] + weight) {
        upper[end] = upper[from] + weight;

        // N번째에 최단 거리 갱신된다면 음수 사이클 존재
        if(i == N)  return true;
      }
    }
  }

  return false;
}

void solve(int start) {
  if(bellmanFord(start))
    cout << -1;
  else {
    for(int i = 2; i <= N; i++) {
      if (upper[i] == INF) cout << -1 << endl;
      else                 cout << upper[i] << endl;
    }
  }
}

int main() {
  initialInput();
  solve(1);
  return 0;
}