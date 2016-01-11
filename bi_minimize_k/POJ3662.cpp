#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int, int> PA;
const int INF = 10000000;
struct edge{int to, cost;};
int d[1000];
vector<edge> es[1000];
vector<edge> _es[1000]; // 辺のコスト 0 or 1 のグラフ
int N, P, K;

//------- 条件 C(x) を満たす最小の x を求める二分探索
// 条件を満たすかどうかの関数
bool C(int x) {
  // _es の初期化
  for (int i = 0; i < N; i++) {
    int m = _es[i].size();
    for (int j = 0; j < m; j++) {
      if (es[i][j].cost <= x)
        _es[i][j].cost = 0;
      else
        _es[i][j].cost = 1;
    }
  }
  // ダイクストラ
  // pair は (最短距離、頂点番号)
  priority_queue<PA, vector<PA>, greater<PA> > qu;
  fill(d, d + N, INF);
  d[0] = 0;
  qu.push(PA(0, 0));
  while (!qu.empty()) {
    PA p = qu.top(); qu.pop();
    int v = p.second;
    if (d[v] < p.first) continue;
    for (int i = 0; i < _es[v].size(); i++) {
      edge e = _es[v][i];
      if (d[e.to] > d[v] + e.cost) {
        d[e.to] = d[v] + e.cost;
        qu.push(PA(d[e.to], e.to));
      }
    }
  }

  return d[N - 1] <= K;
}

// 二分探索
int bi_search() {
  int lb = -1, ub = INF;

  while (ub - lb > 1) {
    int mid = (lb + ub) / 2;
    if (C(mid)) ub = mid;
    else lb = mid;
  }

  return ub;
}

int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif

  // 入力
  cin >> N >> P >> K;
  int a, b, l;
  while (P--) {
    cin >> a >> b >> l;
    a--; b--;
    edge e1 = {b, l};
    edge e2 = {a, l};
    es[a].push_back(e1);
    es[b].push_back(e2);
    _es[a].push_back(e1);
    _es[b].push_back(e2);
  }


  int res = bi_search();
  if (res == INF) res = -1;

  cout << res << endl;
}
