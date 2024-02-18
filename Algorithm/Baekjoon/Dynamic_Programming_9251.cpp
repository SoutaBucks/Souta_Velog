#include <iostream>
#include <vector>
#include <string>


using std::cin;
using std::cout;
using std::vector;
using std::endl;
using std::string;
using std::max;

string firstString = "", secondString = "";
vector<vector<int>> memo(1001, vector<int>(1001, 0));

void showMemo() {
  for(auto & line : memo) {
    for(int & i : line)
      cout << i << " ";
    cout << endl;
  }
}

int getMaxVectorValue() {
  int result = 0;
  for(int i = 1; i <= firstString.length(); i++) {
    for(int j = 1; j <= secondString.length(); j++)
      result = max(result, memo[i][j]);
  }
  return result;
}

int solve() {

  for(int i = 1; i <= firstString.length(); i++) {
    for(int j = 1; j <= secondString.length(); j++) {
      if(firstString[i - 1] == secondString[j - 1])
        memo[i][j] = memo[i - 1][j - 1] + 1;
      else
        memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);
    }
  }
  return getMaxVectorValue();
}

int main() {
  cin >> firstString >> secondString;
  //showMemo();
  cout << solve() << endl;
}