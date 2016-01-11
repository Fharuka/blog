/*
[http://poj.org/problem?id=3268:title]
**問題概要
有向グラフの単一始点（と単一終点）最短経路問題。
**解法
負の経路がないのでダイクストラ法で解ける。単一終点問題は辺の向きを逆にすれば単一始点問題に帰着できる。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int, int> P;
const int INF = 100000000;
const int MAX_N = 1000;
struct edge{int to, cost;};

int main() {
  // ifstream cin("../test.txt");
  int N, M, X;
  cin >> N >> M >> X;
  X--;
  // 行きと帰り
  vector<edge> path[2][MAX_N];
  int f, t, c;
  for (int i = 0; i < M; i++) {
    cin >> f >> t >> c;
    f--; t--;
    edge e1 = {t, c};
    edge e2 = {f, c};
    path[0][f].push_back(e1);
    path[1][t].push_back(e2);
  }

  // pairは(最短距離、頂点の番号)
  priority_queue<P, vector<P>, greater<P> > qu;

  // dの初期化
  int d[2][MAX_N];
  fill(d[0], d[0] + N, INF);
  fill(d[1], d[1] + N, INF);
  d[0][X] = 0; d[1][X] = 0;

  // 行きと帰りで2回ダイクストラ
  for (int i = 0; i < 2; i++) {
    qu.push(P(0, X));
    while (!qu.empty()) {
      P p = qu.top();
      qu.pop();
      int v = p.second;
      if (d[i][v] < p.first) continue;
      for (int j = 0; j < path[i][v].size(); j++) {
        edge e = path[i][v][j];
        if (d[i][e.to] > d[i][v] + e.cost) {
          d[i][e.to] = d[i][v] + e.cost;
          qu.push(P(d[i][e.to], e.to));
        }
      }
    }
  }

  // 行きと帰りの最大値を探す
  int res = d[0][0] + d[1][0];
  for (int i = 1; i < N; i++) {
    int sum = d[0][i] + d[1][i];
    if (i != X && sum > res)
      res = sum;
  }

  cout << res << endl;
}
