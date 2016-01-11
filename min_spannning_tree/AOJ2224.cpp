/*
*AOJ2224: Save your cat
**問題概要
[http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2224:title]
N個の頂点とM個の辺を持った無向グラフがある。グラフの閉路がすべてなくなるように辺を取り除きたい。辺のコストは辺の長さである。取り除く辺のコストの最小値を求めよ。
2 <= N <= 10000
1 <= M
**解法
辺を取り除くと考えるのではなく、残す辺で全域木を作ると考えれば、これも最大全域木問題になる。クラスカル法で解く。
*/
#include <typeinfo>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
struct edge{ int u, v; double cost; };
vector<edge> es;
int V, E; // 頂点数と辺数

//--------Union-Find木------------
vector<int> par; // 親
vector<int> rnk; // 深さ

// Union-Find木の初期化
void init_union_find(int n) {
  par  = vector<int>(n);
  rnk = vector<int>(n);
  for (int i = 0; i < n; i++) {
    par[i] = i;
    rnk[i] = 0;
  }
}

// 木の根を求める
int find(int x) {
  if (par[x] == x) {
    return x;
  } else {
    return par[x] = find(par[x]);
  }
}

// xとyの属する集合を併合
void unite(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y) return;

  if (rnk[x] < rnk[y]) {
    par[x] = y;
  } else {
    par[y] = x;
    if (rnk[x] == rnk[y]) rnk[x]++;
  }
}

// xとyが同じ集合に属するか否か
bool same(int x, int y) {
  return find(x) == find(y);
}

//----------クラスカル法------------
bool comp(const edge& e1, const edge& e2) {
  return e1.cost > e2.cost; // 大きい順
}
double kruskal() {
  sort(es.begin(), es.end(), comp); // edge.costの大きい順
  init_union_find(V); // Union-Findの初期化
  double res = 0;
  for (int i = 0; i < E; i++) {
    edge e = es[i];
    if (!same(e.u, e.v)) {
      unite(e.u, e.v);
      res += e.cost;
    }
  }
  return res;
}

int main() {
  // 初期化
  cin >> V >> E;
  vector<int> vx = vector<int>(V);
  vector<int> vy = vector<int>(V);
  es = vector<edge>(E);
  for (int i = 0; i < V; i++) {
    cin >> vx[i] >> vy[i];
  }
  double l;
  int p, q;
  double total_cost = 0;
  for (int i = 0; i < E; i++) {
    cin >> p >> q;
    p--; q--;
    l = sqrt(static_cast<double>((vx[p] - vx[q])*(vx[p] - vx[q]) + (vy[p] - vy[q])*(vy[p] - vy[q])));
    edge e = {p, q, l};
    es[i] = e;
    total_cost += l;
  }
  // クラスカル法で最大全域木のコストを計算
  double kr = kruskal();
  // 出力
  printf("%.4f\n", total_cost - kr);
}
