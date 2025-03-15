
#include <iostream>
#include <vector>

using std::cin, std::cout, std::endl, std::vector, std::min;

int N;
vector<vector<int>> board;
vector<vector<int>> dp(101, vector<int>(101, 0));

void initialInput() {
  cin >> N;

  int temp;

  for(int i = 0; i < N; i++) {
    vector<int> line;
    for(int j = 0; j < N; j++) {
      cin >> temp;
      line.push_back(temp);
    }
    board.push_back(line);
  }
}

void showBoard() {
  for(int y = 0; y < N; y++) {
    for(int x = 0; x < N; x++)
      cout << board[y][x] << " ";
    cout << endl;
  }
}

void floydWarshall() {
  for(int i = 0; i < N; i++) {
    for(int y = 0; y < N; y++) {
      for(int x = 0; x < N; x++)
        if(board[y][i] and board[i][x])
          board[y][x] = 1;
    }
  }
}

int main() {
  initialInput();
  floydWarshall();
  showBoard();
  return 0;
}