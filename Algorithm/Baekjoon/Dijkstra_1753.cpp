#include <iostream>
#include <vector>
#include <queue>

/* --------------------------------------------------------------

 * ------------------------------------------------------------*/

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;
using std::vector;
using std::priority_queue;


const int INF = 987654321;
int V, E, startNode;

vector<vector<pair<int, int>>> graph;
vector<int> shortestDistance;

struct comp {
    bool operator()(pair<int, int> A, pair<int, int> B) {
      return A.second >= B.second;
    }
};

priority_queue<pair<int, int>, vector<pair<int, int>>, comp> pq;


bool isExternal(int node) {
  return graph[node].front().first == -1
          and graph[node].front().second == -1;
}

void initialInput() {
  int u, v, w;

  cin >> V >> E;
  cin >> startNode;

  vector<pair<int, int>> temp(1, make_pair(-1, -1));

  for(int i = 0; i < V + 1; i++) {
    graph.push_back(temp);
    shortestDistance.push_back(INF);
  }

  // 방향 그래프이므로 한쪽에서만 출발하면 된다.
  for(int i = 0; i < E; i++) {
    cin >> u >> v >> w;
    if(isExternal(u)) {
      graph[u].front().first = v;
      graph[u].front().second = w;
    } else {
      graph[u].emplace_back(v, w);
    }
  }

}

void pqClear() {
  while(not pq.empty())
    pq.pop();
}


void showGraph() {
  for(const auto& r : graph) {
    for(auto a : r)
      cout << "(" << a.first << ", " << a.second << ") ";
    cout << endl;
  }
}

void showDistance() {
  for(const auto& r : shortestDistance)
    cout << r << " ";
  cout << endl;
}

void dijkstra(int start) {
  pqClear();
  // Priority_Queue에 방문할 노드 저장
  pq.emplace(start, 0);
  // 시작 노드는 최소 거리가 0이다.
  shortestDistance[start] = 0;

  while(not pq.empty()) {
    //showDistance();
    int hereNode = pq.top().first;
    int hereLength = pq.top().second;
    pq.pop();
    // dist[hereNode] < cost 라면 무시한다
    if(shortestDistance[hereNode] < hereLength) continue;
    // 현재 Node의 모든 인접 Node들을 방문한다
    for(int i = 0; i < graph[hereNode].size(); i++) {
      // 갈 수 있는 곳이 없다면 break
      if(isExternal(hereNode)) break;
      int nextNode = graph[hereNode][i].first;
      // 현재 노드에서 해당 노드까지의 거리 + 현재 노드까지 오면서 걸린 거리
      int nextLength = graph[hereNode][i].second + hereLength;
      // 다음 노드까지의 최단 거리를 구했다면 경로 교체
      if(shortestDistance[nextNode] > nextLength) {
        shortestDistance[nextNode] = nextLength;
        pq.emplace(nextNode, nextLength);
      }
    }
  }
}

void solve(int start) {
  dijkstra(start);
  for(int i = 1; i < shortestDistance.size(); i++) {
    if(shortestDistance[i] == INF) cout << "INF" << endl;
    else         cout << shortestDistance[i] << endl;
  }
}


int main() {
  initialInput();
  //showGraph();
  solve(startNode);

  return 0;
}