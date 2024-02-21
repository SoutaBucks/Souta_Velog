#include <iostream>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::queue;

int solve(int num) {
  queue<int> queue1;
  int DeleteOrMove = 1; // 1일때 버리고 -1이라면 맨 밑으로 넣는다

  // 1부터 N까지의 카드를 큐에 넣는다
  for(int i = 1; i <= num; i++)
    queue1.push(i);

  while(queue1.size() != 1) {
    if(DeleteOrMove == 1)
      queue1.pop();
    else {
      queue1.push(queue1.front());
      queue1.pop();
    }

    DeleteOrMove *= -1;
  }

  return queue1.front();
}

int main() {
  int N;
  cin >> N;
  cout << solve(N) << endl;

  return 0;
}