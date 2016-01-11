/*
*POJ2395: Out of Hay
[http://poj.org/problem?id=2395:title]
**問題概要
最小全域木の中にある最大コストの辺を求める。
**解法
単純なクラスカル法。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int MAX_M = 10000;
struct edge{ int u, v, cost; };
edge es[MAX_M];
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
  return e1.cost < e2.cost;
}
int kruskal() {
  sort(es, es + E, comp); // edge.costの小さい順
  init_union_find(V); // Union-Findの初期化
  // res は最大辺の長さ
  int res = 0;
  for (int i = 0; i < E; i++) {
    edge e = es[i];
    if (!same(e.u, e.v)) {
      unite(e.u, e.v);
      res = max(res, e.cost);
    }
  }
  return res;
}

int main() {
  // 初期化
  cin >> V >> E;
  int a, b, l;
  for (int i = 0; i < E; i++) {
    cin >> a >> b >> l;
    a--; b--;
    edge e = {a, b, l};
    es[i] = e;
  }
  // 最小全域木をクラスカル法で求める
  int res = kruskal();
  // 出力
  cout << res << endl;
}
