#include <iostream>
#include <deque>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::deque;
using std::vector;
using std::pair;
using std::make_pair;

int boardSize, appleCount, changeWayCount, bodySize = 0;  // 보드 크기, 사과 수, 방향 전환 수, 몸통 길이
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}; // 오른쪽, 아래, 왼쪽, 위
vector<pair<int, int>> applePositions;          // 사과 위치 저장용
vector<pair<int, char>> changeInformations;     // 방향 전환 저장용
deque<pair<int, int>> snack;                    // 뱀 위치 저장

// 움직일 뱀 머리가 보드안에 위치하는가?
bool isInBoard(const pair<int, int>& nextPlace) {
  return ((nextPlace.first > 0 && nextPlace.first <= boardSize) &&
          (nextPlace.second > 0 && nextPlace.second <= boardSize));
}
// 움직일 뱀 머리가 뱀 몸통과 부딪히는가?
bool isSnackBody(const pair<int, int>& nextPlace) {
  bool answer = false;

  /* 1. Deque에서 앞에서 하나씩 뽑는다.
   * 2. 뽑은 것을 뱀의 머리가 위치할 위치와 비교해본다
   * 3. 비교 후 맞다면 true를 반환한다
   * 4. 비교 후 다시 Deque의 뒤로 넣는다
   */

  for(int i = 0; i < bodySize; i++) {
    pair<int, int> snackBody = snack.front();
    if((nextPlace.first == snackBody.first) && (nextPlace.second == snackBody.second))
      answer = true;
    snack.push_back(snackBody);
    snack.pop_front();
  }

  return answer;
}

// 뱀의 머리가 움직일 수 있는지
bool isLegal(const pair<int, int>& nextPlace) {
  return isInBoard(nextPlace) && !isSnackBody(nextPlace);
}

// 뱀의 머리가 위치하는 곳이 사과인지
bool isApple(const pair<int, int>& nextPlace) {
  bool answer = false;

  for(int i = 0; i < appleCount; i++) {

    int appleX = applePositions[i].first, appleY = applePositions[i].second,
        nextPlaceX = nextPlace.first, nextPlaceY = nextPlace.second;

    if((nextPlaceX == appleX) && (nextPlaceY == appleY)) {
      answer = true;
      applePositions.erase(applePositions.begin() + i);
      appleCount--;
      break;
    }
  }

  return answer;
}

// 방향 전환 관련 함수
int getNextDelta(int second, int nowDelta) {
  int nextDelta = nowDelta;

  for(int i = 0; i < changeWayCount; i++) {
    if(second == changeInformations[i].first) {
      if(changeInformations[i].second == 'D') {
        nextDelta++;
        nextDelta %= 4;
      } else {
        nextDelta--;
        if(nextDelta < 0)
          nextDelta += 4;
      }
      break;
    }
  }

  return nextDelta;
}

int solve() {
  int answer, delta = 0;  // 오른쪽 0 | 아래 1 | 왼쪽 2 | 위 3,
  bodySize = 1;  // bodySize = 1 기본 뱀 길이
  snack.push_back(make_pair(1, 1));

  for(int i = 1; ;i++) {
    // 현재 머리의 위치
    int headX = snack.front().first, headY = snack.front().second;
    // 다음 위치
    pair<int, int> nextPlace = make_pair(headX + dx[delta], headY + dy[delta]);

    // 위치에 갈 수 있다면
    if(isLegal(nextPlace)) {
      snack.push_front(nextPlace);  // 새 위치가 머리가 된다

      // 방향 전환
      delta = getNextDelta(i, delta);

      // 사과가 아니면 꼬리를 하나 줄여야 한다
      if(!isApple(nextPlace))
        snack.pop_back();
      else
        // 아니면 꼬리를 그대로 둔다
        bodySize++;
    } else {
      answer = i;
      break;
    }
  }

  return answer;
}

void initialSetting() {
  cin >> boardSize >> appleCount;
  for(int i = 0; i < appleCount; i++) {
    pair<int, int> position;
    cin >> position.first >> position.second;
    applePositions.push_back(position);
  }
  cin >> changeWayCount;
  for(int i = 0; i < changeWayCount; i++) {
    pair<int, char> information;
    cin >> information.first >> information.second;
    changeInformations.push_back(information);
  }
}

int main() {
  initialSetting();
  cout << solve() << endl;
}