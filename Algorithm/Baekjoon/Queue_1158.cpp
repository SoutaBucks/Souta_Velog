#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::vector;

int N, K;
queue<int> queue1;
vector<int> answer;

void showAnswer() {
  cout << "<";
  for(int i = 0; i < N; i++)
    cout << answer[i] << (i != N - 1 ? ", " : ">");
}

void initalQueue() {
  for(int i = 1; i <= N; i++)
    queue1.push(i);
}

void solve() {
  initalQueue();

  int turn = 1; // K와 같으면 그 순서를 제거한다

  while(!queue1.empty()) {
    if(turn == K) {
      turn = 0;
      answer.push_back(queue1.front());
    }
    else
      queue1.push(queue1.front());

    queue1.pop();
    turn++;
  }

  showAnswer();
}

int main() {
  cin >> N >> K;
  solve();

  return 0;
}