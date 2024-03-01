#include <iostream>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::ios;
using std::priority_queue;

// compare을 위한 구조체 선언
struct compare {
    bool operator()(int a, int b) {
      return a > b;
    }
};

priority_queue<int, vector<int>, compare> heap;

void solve() {
  int N, x;
  cin >> N;
  while(N--) {
    cin >> x;
    if(x == 0) {        // 0이라면 Heap에서 자연수를 빼내야 한다
      if(heap.empty())  // Heap이 비어있으면 0을 출력
        cout << "0\n";
      else {            // 아니라면 Heap에서 자연수를 하나 뽑아서 출력
        cout << heap.top() << "\n";
        heap.pop();
      }
    } else              // 아니라면 Heap에서 자연수를 넣는다
      heap.push(x);
  }
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
