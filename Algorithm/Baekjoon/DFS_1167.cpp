#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::pair;
using std::make_pair;
using std::vector;
using std::ios;
using std::max;

int nodeCount, maxWeight = 0;  // 노드 개수, 최대 가중치
vector<vector<pair<int, int>>> tree; // tree
vector<bool> visited;     // 방문 여부
vector<int> lengths;       // Root에서 각 Node까지의 길이를 모아놓은 vector


// 트리를 만드는 함수
void makeTree() {
  cin >> nodeCount;

  for(int i = 0; i <= nodeCount; i++) {
    /* 2차원 벡터의 tree의 row는 각 노드의 번호를 나타낸다
      * col은 각 node에서 갈 수 있는 child와 가중칯값을 pair로 가진다
      * depths는 -1로 초기화한다
      * */
    vector<pair<int,int>> temp;
    tree.push_back(temp);
    visited.push_back(false);
    lengths.push_back(-1);
  }

  /* 트리 간선의 정보를 입력 받는다
   * a는 시작 정점
   * b는 끝 정점
   * w는 a와 b사이의 가중치이다
   * 입력 순서상 a b w b w b w  순서이므로
   * b가 w보다 먼저 입력을 받는다
   * b가 -1이라면 정보를 주는 행위가 끝남을 의미
   * */

  for(int i = 0; i < nodeCount; i++) {
    int a, b, w;
    cin >> a;
      while(true) {
        cin >> b;
        if(b == -1) break;
        cin >> w;
        maxWeight = max(maxWeight, w);      // 가중치 최대 값 구하기기
       tree[a].push_back(make_pair(b, w)); // 여기가 오류...
      }
  }
}

/* 해당 노드에서 방문할 수 있는 노드를 이미 다 방문 했다면
 * 그 노드는 Leaf노드이다
 * */
bool isLeaf(int here) {
  bool flag = true;

  for(auto & canGo : tree[here]) {
    int canGoNext = canGo.first;
    if(!visited[canGoNext]) {
      flag = false;
      break;
    }
  }

  return flag;
}

void dfs(int here, int weight) {

  if(isLeaf(here)) { // Leaf노드라면 탐색을 끝내자
    lengths[here] = weight;
    return;
  }
  for(int i = 0; i < tree[here].size(); i++) {
    // 다음으로 갈 node번호를 나타내는 next변수
    // weight에 추가될 nextWeight
    int next = tree[here][i].first;
    int nextWeight = tree[here][i].second;

    /* 양방향 tree를 만들었으므로 방문 여부를 저장하지 않는다면
     * 무한 루프에 빠질 수 있다
     * */
    if(!visited[next]) {
      visited[here] = true;
      dfs(next, weight + nextWeight);
    }
  }
}

// length vector를 초기화 하는 함수
void initialLength() {
  for(int i = 0; i <= nodeCount; i++)
    visited[i] = false;
}

void showTree() {
  for(auto & line : tree) {
    for(auto & element : line)
      cout << "(" << element.first << ", " << element.second << ") ";
    cout << "\n";
  }
}

int solve() {
  int answer = 0, whereToStart = 0; // 답, 시작 점

  dfs(1, 0);        // 임의로 Root를 잡고 dfs를 통해 가장 길이가 먼 노드를 찾는다
  // 가장 긴 길이를 가지는 length 노드 번호를 찾는 함수
  for(int i = 1; i <= nodeCount; i++) {
    if(answer < lengths[i]) {
      answer = lengths[i];
      whereToStart = i;
    }
  }

  initialLength();
  dfs(whereToStart, 0);        // 찾은 노드로부터 다시 dfs를 시작해 가장 긴 곳을 찾으몀 그게 답이다.

  answer = 0;
  for(auto & i : lengths) {
    if(answer < i)
      answer = i;
  }

  return answer;
}

int main() {
  /* 아래 3문장은
   * 출력과 입력을 빠르게 하기 위해서 적는 문장이다.
   * */
  cin.tie(NULL);
  cout.tie(NULL);
  ios::sync_with_stdio(false);

  makeTree();
  //showTree();
  cout << solve();

  return 0;
}
