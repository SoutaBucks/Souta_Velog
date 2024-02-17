#include <iostream>
#include <vector>

using namespace std;

int sizeOfMatrix = 0;
vector<vector<int>> matrix;       // 입력받은 행렬
vector<vector<int>> answerVector; // 답 행렬

// 행렬을 만드는 함수
void makeMatrix() {
  for(int i = 0; i < sizeOfMatrix; i++) {
    vector<int> temp;
    for(int j = 0; j < sizeOfMatrix; j++) {
      int n;
      cin >> n;
      temp.push_back(n);
    }
    matrix.push_back(temp);
  }
}

// 답 행렬을 출력하는 함수
void showAnswerMatrix() {
  for(auto line : answerVector) {
    for(int & i : line) {
      cout << i << " ";
    }
    cout << endl;
  }
}

// 행렬 2개의 곱셈을 하는 함수
vector<vector<int>> multiplyMatrix(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix) {
  vector<vector<int>> resultMatrix(sizeOfMatrix, vector<int>(sizeOfMatrix, 0));

  for(int i = 0; i < sizeOfMatrix; i++) {
    for(int j = 0; j < sizeOfMatrix; j++) {
      for(int k = 0; k < sizeOfMatrix; k++)
        resultMatrix[i][j] += (firstMatrix[i][k] * secondMatrix[k][j]);
      resultMatrix[i][j] %= 1000;
    }
  }

  return resultMatrix;
}

// 항등 행렬을 반환하는 함수
vector<vector<int>> getIdentityMatrix() {
  vector<vector<int>> resultMatrix(sizeOfMatrix, vector<int>(sizeOfMatrix, 0));

  for(int i = 0; i < sizeOfMatrix; i++) {
    for(int j = 0; j < sizeOfMatrix; j++) {
      if(i == j)
        resultMatrix[i][j] = 1;
    }
  }

  return resultMatrix;
}

// 거듭 제곱을 수행하는 함수
vector<vector<int>> doPowerMatrix(long long power) {
  if(power == 0) return getIdentityMatrix();
  if(power % 2 != 0) return multiplyMatrix(doPowerMatrix(power - 1), matrix);
  vector<vector<int>> memo = doPowerMatrix(power / 2);
  return multiplyMatrix(memo, memo);
}

int main() {
  long long powerNum = 0;
  cin >> sizeOfMatrix >> powerNum;
  makeMatrix();
  answerVector = doPowerMatrix(powerNum);
  showAnswerMatrix();

  return 0;
}