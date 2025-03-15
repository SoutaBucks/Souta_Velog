
#include <iostream>
#include <vector>

using std::cin, std::cout, std::endl, std::vector, std::min;

const int INF = 987654321;
int N, M, a, b, c;
vector<vector<int>> board(101, vector<int>(101, INF));

void initialInput() {
  cin >> N >> M;

  // 시작과 도착지점이 같은 경우는 존재하지 않는다
  for(int i = 1; i <= N; i++)
    board[i][i] = 0;

  for(int i = 1; i <= M; i++) {
    cin >> a >> b >> c;
    if((board[a][b] != INF and c < board[a][b]) or (board[a][b] == INF))
      board[a][b] = c;
  }
}

void showBoard() {
  for(int y = 1; y <= N; y++) {
    for(int x = 1; x <= N; x++) {
      cout << ((board[y][x] == INF) ? 0 : board[y][x]) << " ";
    }
    cout << endl;
  }
}

void floydWarshall() {
  for(int i = 1; i <= N; i++) {
    for(int y = 1; y <= N; y++) {
      for(int x = 1; x <= N; x++)
        board[y][x] = min(board[y][x], board[y][i] + board[i][x]);
    }
  }
}

int main() {
  initialInput();
  floydWarshall();
  showBoard();
  return 0;
}