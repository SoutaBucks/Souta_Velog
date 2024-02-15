#include <iostream>
#include <string>

using namespace std;

int NUM;

int charToNumber(char c) {
    return c - '0';
}

int constructorOfNumber(int n) {
    int result = 0;
    string numString = to_string(n);
    for(char & c : numString)
        result += charToNumber(c);
    return result + n;
}

int solve() {
    int answer = 0;
    cin >> NUM;
    for(int i = 1; i <= NUM; i++) {
        if(constructorOfNumber(i) == NUM) {
            answer = i;
            break;
        }
    }
    return answer;
}

int main() {
    cout << solve() << endl;
}