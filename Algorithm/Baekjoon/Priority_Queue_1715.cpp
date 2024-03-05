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
      return a > b;         // 작은 값이 위로 올라간다
    }
};

priority_queue<int, vector<int>, compare> heap;

/* 최대한 작은 카드끼리 더하는 것을 반복하는 작업
 * */
void solve() {
  int N, cardCount, mixedCard, answer = 0;
  cin >> N;

  while(N--) {
    cin >> cardCount;
    heap.push(cardCount);
  }

  while(!heap.empty()) {
    mixedCard = 0;
    if(heap.size() == 1) break;
    mixedCard += heap.top();  // 첫번째로 작은 카드와
    heap.pop();
    mixedCard += heap.top();  // 두번째로 작은 카드를 더한다
    heap.pop();
    heap.push(mixedCard);     // 더한 카드를 Heap에 넣는다
    answer += mixedCard;      // 비교 횟수만을 answer에 넣는다.
  }

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
