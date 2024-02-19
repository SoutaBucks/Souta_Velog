#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::stack;
using std::string;
using std::reverse;

string originalString, explodeString;
bool canExplode = true; // 문자열 폭발 조건에 부합한다
stack<char> stackLeft, stackRight;  // stackLeft - 일반 문자열 stackRight - 폭발 가능한 문자열

// 일반 문자열에서 폭발 후보 문자열을 빼내는 함수
void popExplodeString() {
  stackRight.push(stackLeft.top());
  stackLeft.pop();
}

// explodeString의 Index번째 문자가 일치하는지 여부를 반환하는 함수
bool charIsSameWithExplodeString(int index) {
  /* 비교해야할 폭발 문자열이 남아있는데 stackLeft의 문자가 없다면 폭발 문자열이 아니다
   * stackLett의 가장 위의 문자와 explodeString의 Index번째 문자가 같다면 폭발 문자열이 될 수 있다
   * */
  return (!stackLeft.empty() && (stackLeft.top() == explodeString[index]));
}

string getExplodedString() {
  string answerString;

  while(!stackLeft.empty()) {
    answerString += stackLeft.top();
    stackLeft.pop();
  }
  reverse(answerString.begin(), answerString.end());

  return answerString != "" ? answerString : "FRULA";
}

string solve() {
  int explodeLength = explodeString.length();

  for(char & i : originalString) {
    canExplode = true;    // default - 폭발 가능한 상태
    stackLeft.push(i);    // stackLeft에 일반 문자열을 하나 씩 Insert
    if(stackLeft.top() == explodeString[explodeLength - 1]) { // stackLeft에 들어있는 가장 마지막 문자와 폭발 문자열의 마지막 문자가 같다 | exploadedLegnth에서 1을 빼야 Index가 가장 뒤에 위치할 수 있다.
      popExplodeString();
      for(int j = explodeLength - 2; j >= 0; j--) {           // 폭발 문자열의 뒤에서부터 문자열을 하나씩 대조해본다 | 가장 뒤의 Index는 이미 비교했으므로 그 다음 가장 뒤의 Index부터 비교해야한다.
        if(charIsSameWithExplodeString(j))
          popExplodeString();
        else {     // 폭발 문자열의 조건에 부합하지 않는다
          canExplode = false; // 폭발 불가능
          break;
        }
      }

      while (!stackRight.empty()) {   // stackRignt에 들어있는 폭발 문자열을 비우자
        if(!canExplode)               // 폭발 할 수 없다면 일반 문자열이므로 stackLeft에 돌려 놓자
          stackLeft.push(stackRight.top());
        stackRight.pop();
      }

    }
  }

  return getExplodedString();
}

int main() {
  cin >> originalString >> explodeString;
  cout << solve() << endl;

  return 0;
}