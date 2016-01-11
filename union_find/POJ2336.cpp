/*
  単純なUnion-Find木の問題
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

//--------Union-Find木---------
vector<int> par; // 親
vector<int> rnk; // 深さ

// Union-Find木の初期化
void init(int n) {
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
//-------------------------



int main() {
  // ifstream cin("../test.txt");
  // 入力
  int N, d;
  cin >> N >> d;
  d *= d; // 距離は2乗しておく
  vector<int> x(N), y(N);
  for (int i = 0; i < N; i++) {
    cin >> x[i] >> y[i];
  }
  // 修理されたコンピュータ
  vector<bool> repaired(N, false);
  // Union-Find木の初期化
  init(N);

  // 操作の読み込みはファイル終端までループ
  char op;
  while (cin >> op) {
    if (op == 'O') {
      int r;
      cin >> r;
      repaired[--r] = true;
      // union-find木の併合
      for (int i = 0; i < N; i++) {
        if (repaired[i] && (x[r] - x[i])*(x[r] - x[i]) + (y[r] - y[i])*(y[r] - y[i]) <= d) {
          unite(r, i);
        }
      }

    } else if (op == 'S') {
      int a, b;
      cin >> a >> b;
      a--; b--;
      if (same(a, b)) {
        cout << "SUCCESS" << endl;
      } else {
        cout << "FAIL" << endl;
      }
    }
  }
}
