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
struct compareLeft {
    bool operator()(int a, int b) {
      return a < b;         // 큰 값이 위로 올라간다
    }
};

struct compareRight {
    bool operator()(int a, int b) {
      return a > b;         // 작은 값이 위로 올라간다
    }
};


priority_queue<int, vector<int>, compareLeft> heapLeft;
priority_queue<int, vector<int>, compareRight> heapRight;


// 지금까지 넣은 수의 개수가 홀수인지 확인하는 함수
bool isOdd(int size) {  return (size % 2 != 0); }

/* 가운데 수를 구하기 위해 올바르게 push하는 함수
 * 여태까지 넣은 수의 반반만큼 각 heap에 들어가게끔 해야한다
 * 1. left.top보다 크거나 같아면 right에 넣는다
 * right의 크기가 left보다 크다면 left로 하나 보낸다
 * 2. left.top보다 작으면 left에 넣는다
 * left의 크기가 right + 1 보다 크다면 right로 하나 보낸다
 * 왜 right + 1인가?
 * solve의 cout 부분에보면 heapLeft.top()을 출력하는 부분이있다.
 * 짝수의 경우 둘 중 작은 값을 출력해야하고 홀수의 경우는 가운데 수를 출력하면 된다
 * 둘 다 heapLeft에서 값을 출력하게끔 코드를 만들기 위해 기본적으로
 * leftSize와 rightSize의 크기를 같거나 leftSize가 하나더 크게끔 해놓았다
 * 3. 동일한 수가 들어오면 left와 right의 top을 비교해서 해당하는 범위의 heap에 넣는다
 * */
void pushHeap(int num, int size) {
  int leftSize = heapLeft.size(), rightSize = heapRight.size();
  if(heapLeft.top() <= num) {
    heapRight.push(num);
    rightSize++;
    if(leftSize < rightSize)  {
      heapLeft.push(heapRight.top());
      heapRight.pop();
    }
  }
  else {
    heapLeft.push(num);
    leftSize++;
    if(leftSize > rightSize + 1) {  // 홀수, 짝수의 경우 둘 다 left에서 값을 답으로 구하기 위해
      heapRight.push(heapLeft.top());
      heapLeft.pop();
    }
  }
}

/* 최대한 작은 카드끼리 더하는 것을 반복하는 작업
 * */
void solve() {
  int N, num;
  cin >> N;
  for(int i = 1; i <= N; i++) {
    cin >> num;
    if(i == 1) {
      cout << num << "\n";
      heapLeft.push(num);
    }
    else {
      pushHeap(num, i);
      cout << heapLeft.top() << "\n";
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
