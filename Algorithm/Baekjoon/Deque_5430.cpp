#include <iostream>
#include <deque>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::deque;
using std::string;
using std::stoi;

int T, N , isReversed;
string functions, array;
deque<int> deque1;

// 답을 출력하는 함수
void showAnswer() {
  cout << "[";

  if(deque1.empty())
    cout << "]";

  if(isReversed != -1) {
    while(!deque1.empty()) {
      cout << deque1.back();
      deque1.pop_back();
      cout << (deque1.empty() ? "]" : ",");
    }
  } else {
    while(!deque1.empty()) {
      cout << deque1.front();
      deque1.pop_front();
      cout << (deque1.empty() ? "]" : ",");
    }
  }
  cout << endl;
}

// Deque에 array 값을 넣는 함수
void initialDeque() {
  string numString = "";
  for(char & c : array) {
    if(isdigit(c))
      numString += c;
    else if(c == ',') {
      deque1.push_back(stoi(numString));
      numString = "";
    }
  }
  // 마지막 수열의 숫자도 deque에 저장한다
  if(numString != "")
    deque1.push_back(stoi(numString));
}

void solve() {
  initialDeque();

  for(char & c : functions) {
    if(c == 'R')
      isReversed *= -1;
    else {
      if(deque1.empty()) {
        cout << "error" << endl;
        return;
      }

      (isReversed != -1) ? deque1.pop_back() : deque1.pop_front();
    }
  }

  showAnswer();
}

int main() {
  cin >> T;   // Test Case 개수
  while(T--) {
    isReversed = -1;  // 1이라면 Reversed Array, -1이라면 Not Reversed Array
    cin >> functions; // 함수 입력
    cin >> N;         // 배열 숫자 개수 입력
    cin >> array;     // 배열 입력
    solve();
  }

  return 0;
}