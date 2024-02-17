#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::cin;
using std::min;


vector<int> memo(5000, 0);

int solve(int weight) {
  if(weight == 0) return 0;   // 모든 설탕을 다 든 경우 끝
  if(memo[weight] != 0) return memo[weight];  // memo 되어있다면 memo값 반환

  int firstCase = 987654321, secondCase = 987654321;

  if(weight - 3 >= 0)   // 3kg를 들 수 있다면
    // 3kg 를 뺀 나머지 무게를 최소한으로 들 수 있는 봉지 수 or 3kg를 뺀 나머지 무게로 다시 solve해보기
    // + 1은 3kg 봉지를 들기 때문에 1봉지를 추가한다는 의미
    firstCase = min(memo[weight - 3], solve(weight - 3)) + 1;
  if(weight - 5 >= 0)
    secondCase = min(memo[weight - 5], solve(weight - 5)) + 1;

  // 3kg 또는 5kg 중 더 적게 드는 방법을 고르자
  memo[weight] = min(firstCase, secondCase);

  return memo[weight];
}

int main() {
  int sugarWeight = 0, result = 0;
  cin >> sugarWeight;
  result = solve(sugarWeight);
  /* 왜 >= 987654321 일까?
   * 7의 경우 3 또는 5kg로 1봉지 정도 들 수 있다
   * 위의 함수에서 +1이 존재하므로 987654321보다 큰 값을 받을 수 있다.
   * */
  cout << (result >= 987654321 ? -1 : result) << endl;
  return 0;
}