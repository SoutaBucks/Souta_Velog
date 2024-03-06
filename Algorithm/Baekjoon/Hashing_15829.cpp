#include <iostream>
#include <vector>
#include <string>


using std::cin;
using std::cout;
using std::vector;
using std::ios;
using std::string;

const long long M = 1234567891;
int stringSize = 0;
string inputString;

// a -> 1, b -> 2 ... 식으로 변환하는 함수
int getAlphabetValue(char c) {
  return c - 'a' + 1;
}

// Hash 값을 얻는 함수
int getHashValue() {
  long long result = 0, r = 1;

  for(int i = 0; i < stringSize; i++) {
    result = (result + (getAlphabetValue(inputString[i]) * r)) % M;
    r = (r * 31) % M;
  }

  return result;
}

void solve() {
  cin >> stringSize;
  cin >> inputString;
  cout << getHashValue();
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
