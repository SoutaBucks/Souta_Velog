#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::ios;

int nodeCount;  // 노드 개수
vector<vector<int>> tree; // tree
vector<bool> visited;     // 방문 여부
vector<int> answer;       //정답

// 트리를 만드는 함수
void makeTree() {
  cin >> nodeCount;

  for(int i = 0; i <= nodeCount; i++) {
    /* 2차원 벡터의 tree의 row는 각 노드의 번호를 나타낸다
     * col은 각 node에서 갈 수 있는 child를 나타낸다
     * -1만 들어있는 row는 leaf 노드임을 의미한다
     * answer은 그냥 -1로 초기화하는 과정이다
     * */
    vector<int> temp = {-1};
    tree.push_back(temp);
    visited.push_back(false);
    answer.push_back(-1);
  }

  // 양방향 트리를 만든다
  for(int i = 0; i < nodeCount - 1; i++) {
    int a, b;
    cin >> a >> b;
    tree[a].push_back(b);
    tree[b].push_back(a);
  }
}

// Leaf 노드 여부를 반환
// -1만 들어있다면 Leaf 노드이므로 길이가 1임을 확인한다
bool isLeaf(int here) {
  return tree[here].size() == 1;
}

void dfs(int here) {

  if(isLeaf(here)) return;  // Leaf노드라면 탐색을 끝내자

  for(int i = 1; i < tree[here].size(); i++) {
    // 다음으로 갈 node번호를 나타내는 next변수
    int next = tree[here][i];

    /* 양방향 tree를 만들었으므로 방문 여부를 저장하지 않는다면
     * 무한 루프에 빠질 수 있다
     * */
    if(!visited[next]) {
      visited[here] = true;
      dfs(next);
      visited[here] = false;

      // 부모를 찾는 것이 정답이다
      answer[next] = here;
    }
  }
}

void solve() {
  dfs(1); // 1이 root이다 (문제에 적혀있다)

  // 정답을 cout한다
  for(int i = 2; i <= nodeCount; i++)
    cout << answer[i] << "\n";
}

int main() {
  /* 아래 3문장은
   * 출력과 입력을 빠르게 하기 위해서 적는 문장이다.
   * */
  cin.tie(NULL);
  cout.tie(NULL);
  ios::sync_with_stdio(false);

  makeTree();
  solve();

  return 0;
}

