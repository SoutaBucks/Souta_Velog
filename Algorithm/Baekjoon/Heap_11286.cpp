#include <iostream>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::ios;
using std::priority_queue;

/* compare을 위한 구조체 선언
 * return 값이 true라면 swap이 된다.
 * */
struct compare {
    bool operator()(int a, int b) {
      if(abs(a) == abs(b)) return a > b;    // 절댓값이 같다면 음수가 위로 올라온다
      else  return abs(a) > abs(b);         // 절댓값이 작은 값이 위로 올라간다
    }
};

priority_queue<int, vector<int>, compare> heap;

void solve() {
  int N, x;
  cin >> N;
  while(N--) {
    cin >> x;
    if(x == 0) {
      if(heap.empty())
        cout << "0\n";
      else {
        cout << heap.top() << "\n";
        heap.pop();
      }
    } else {
      heap.push(x);
    }
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
