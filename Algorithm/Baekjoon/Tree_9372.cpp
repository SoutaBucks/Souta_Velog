#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::ios;

void solve() {
  int T, N, M;
  cin >> T;
  while(T--) {
    cin >> N >> M;
    int a, b;
    while(M--) {
      cin >> a >> b;
    }

    /* 엥...? 왜 N-1인데..?
     * 노드가 N개인 그래프는 최소 N-1개의 간선을 가진다 (그래프 성질)
     * 이 문제에서는 최소 간선의 개수를 구하는 문제이고,
     * 모든 노드는 서로 연결되어있는 연결 그래프이다.
     * 위의 성질에 의해 N - 1 개 이상의 간선이 존재할 것이므로
     * 최소 간선 개수인 N - 1이 답이다.
     * */
    cout << N-1 << "\n";
  }
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

