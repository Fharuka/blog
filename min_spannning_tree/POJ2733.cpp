/*
*POJ2377: Bad Cowtractors
**問題概要
[http://poj.org/problem?id=2377:title]
最小全域木、ではなく、「最大」全域木を作る問題。
つまり、コストの和が最大になるような全域木を作る。
**解法
クラスカル法。辺のソートをコストの大きい順にするだけ。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int MAX_E = 20000;
struct edge{ int u, v, cost; };
edge es[MAX_E];
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
int kruskal() {
  sort(es, es + E, comp); // edge.costの大きい順
  init_union_find(V); // Union-Findの初期化
  int res = 0;
  int cnt_e = 0; // 加える辺を数える
  for (int i = 0; i < E; i++) {
    edge e = es[i];
    if (!same(e.u, e.v)) {
      unite(e.u, e.v);
      res += e.cost;
      cnt_e++;
    }
  }
  if (cnt_e == V - 1) {
    return res;
  } else {
    return -1; // 全域木を作れなければ-1
  }
}
int main() {
  // ifstream cin("../test.txt");
  // 初期化
  cin >> V >> E;
  int a, b, c;
  for (int i = 0; i < E; i++) {
    cin >> a >> b >> c;
    a--; b--;
    edge e = {a, b, c};
    es[i] = e;
  }
  // クラスカル法で最大全域木を計算
  int max_cost = kruskal();
  // 出力
  cout << max_cost << endl;
}
