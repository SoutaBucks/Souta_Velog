#include <iostream>
#include <vector>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::stack;
using std::string;

string solve(string str) {
  stack<char> stack1;
  for(char & c : str) {
    if(c == '(')
      stack1.push(c);
    else if(c == ')') {
      if(stack1.empty())
        return "NO";
      stack1.pop();
    }
  }

  return stack1.empty() ? "YES" : "NO";
}

int main() {
  int n;
  cin >> n;
  while(n--) {
    string temp;
    cin >> temp;
    cout << solve(temp) << endl;
  }
}