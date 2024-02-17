#include <iostream>
#include <vector>

using namespace std;

int sizeOfPaper = 0, whitePaper = 0, bluePaper = 0;
int WHITE = 0, BLUE = 1;
vector<vector<int>> paper;

// 종이 만드는 함수
void makePaper() {
  for(int i = 0; i < sizeOfPaper; i++) {
    vector<int> temp;
    for(int j = 0; j < sizeOfPaper; j++) {
      int n;
      cin >> n;
      temp.push_back(n);
    }
    paper.push_back(temp);
  }
}

// 종이 보여주는 함수
void showPaper() {
  for(auto & line : paper) {
    for(int & i : line)
      cout << i << " ";
    cout << endl;
  }
}

// 해당 부분이 1인지 여부 반환
bool isBluePart(int x, int y) {
  return paper[y][x] == 1;
}

// 해당 구역이 하나의 숫자로만 이루어져 있는지 여부 반환
bool isSameColorPaper(int rowStart, int rowFinish, int colStart, int colFinish) {
  int flagColor = paper[rowStart][colStart]; // 기준이 되는 색

  for(int i = rowStart; i < rowFinish; i++) {
    for(int j = colStart; j < colFinish; j++) {
      // 흰색 색종이에 파란색이 섞여있다 or 파란색 색종이에 흰색이 섞여있다
      if((flagColor == WHITE && isBluePart(j, i)) || (flagColor == BLUE && not isBluePart(j, i)))
        return false;
    }
  }

  // 한 가지 색으로 이루어져 있다
  flagColor == WHITE ? whitePaper++ : bluePaper++;
  return true;
}

// 문제 해결하는 함수
void solve(int rowStart, int rowFinish, int colStart, int colFinish)  {

  // 가장 작게 자른 경우
  if(rowStart == rowFinish && colStart == colFinish) {
    isBluePart(colStart, rowStart) ? bluePaper++ : whitePaper++;
    return;
  }

  // 색종이를 잘라야 한다면
  if(not isSameColorPaper(rowStart, rowFinish, colStart, colFinish)) {
    int half = (rowFinish - rowStart) / 2;
    solve(rowStart, rowStart + half, colStart, colStart + half);    // 왼쪽 위
    solve(rowStart + half, rowFinish, colStart, colStart + half);   // 오른쪽 위
    solve(rowStart, rowStart + half, colStart + half, colFinish);   // 왼쪽 아래
    solve(rowStart + half, rowFinish, colStart + half, colFinish);  // 오른쪽 아래
  }
}

int main() {
  cin >> sizeOfPaper;
  makePaper();
  solve(0, sizeOfPaper, 0, sizeOfPaper);
  cout << whitePaper << endl << bluePaper;
  //showPaper();
  return 0;
}