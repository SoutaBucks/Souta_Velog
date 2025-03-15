#include <iostream>
#include <queue>
#include <vector>

/* N - 학생 수
 * X - 정점
 * M - 간선 (단방향)
 * T - 가중치
 * */


using std::cin;
using std::cout;
using std::endl;
using std::priority_queue;
using std::vector;
using std::pair;
using std::make_pair;

vector<vector<pair<int, int>>> graph(1001, vector<pair<int, int>> (1, make_pair(-1, -1)));
vector<vector<pair<int, int>>> upsideDownGraph(1001, vector<pair<int, int>> (1, make_pair(-1, -1)));

int N, M, X, T;

struct compare {
    bool operator()(pair<int, int> a, pair<int, int> b) {
      return a.second < b.second;
    }
};

vector<int> dijkstra(int start) {
  vector<int> distance (N + 1, 987654321);
  priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pqueue;

  distance[start] = 0;
  pqueue.push(make_pair(start, 0));

  while (not pqueue.empty()) {
    int here = pqueue.top().first;
    int cost = pqueue.top().second;

    distance[here] = cost;
    pqueue.pop();

    for(int i = 1; i < graph[here].size(); i++) {
      int there = graph[here][i].first;
      if(distance[there] > cost + graph[here][i].second)
        pqueue.push(make_pair(there, graph[here][i].second + cost));
    }
  }
  return distance;
}

void initialInput() {
  int start, end;

  cin >> N >> M >> X;
  for(int i = 0; i < M; i++) {
    cin >> start >> end >> T;
    graph[start].push_back(make_pair(end, T));
    upsideDownGraph[end].push_back(make_pair(start, T));
  }
}

void changeGraph() {
  graph = upsideDownGraph;
}

/* 1. 목적지 마을에서 다익스트라 후 값 저장
 * 2. 각 출발지에서 다익스트리 후 목적지 마을 값 추출
 * 3. 각 값들을 더한다
 * 4. 최댓값 추출
 * */
int solve() {
  vector<int> endToFirst, eachFirstToEnd;

  endToFirst = dijkstra(X); // 1번
  changeGraph();
  eachFirstToEnd = dijkstra(X); // 2번

  for(int i = 1; i < N + 1; i++)
    endToFirst[i] += eachFirstToEnd[i]; // 3번

  // 4번
  int maxValue = endToFirst[1];
  for(int i = 1; i < N + 1; i++) {
    if(maxValue < endToFirst[i])
      maxValue = endToFirst[i];
  }

  return maxValue;
}

int main() {
  initialInput();
  cout << solve() << endl;

  return 0;
}