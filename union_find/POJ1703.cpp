/*
[http://poj.org/problem?id=1703:title]
**問題概要
町に2つのギャング組織がある。N人の犯罪者について、M個の情報が与えられる。情報は、「犯罪者aと犯罪者bは異なる組織に属する」という形式で与えられる。入力列の途中で「犯罪者aと犯罪者bは同じ組織に属するか？」という質問が与えられるので、それまでに得た情報に基づいて "In the same gang.", "In different gangs.", "Not sure yet." のいずれかを出力するプログラムをかけ。
**解放
Union-Find木を使う。木は 2 * N 個の要素からなる。
0..(N-1)  : 犯罪者i
N..(2N-1) : 番号jは犯罪者j-Nと違う組織に属するという意味
これによって、たとえば union(1, N+2) は、「犯罪者1は、犯罪者2と違う組織に属する」という意味になる。このようにして「違う組織に属する」という情報をうまく処理すれば、あとは単純。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

//------- Union-Find木 ---------
vector<int> par; // 親
vector<int> rnk; // 深さ
// 初期化
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
//-------------------

int main() {
  ifstream cin("../test.txt");
  int testcase;
  cin >> testcase;
  while(testcase--) {
    int N, M, a, b;
    char c;
    cin >> N >> M;
    // Union-Find木の初期化
    // N番目以降はアンチ属性用
    init(2 * N);
    while (M--) {
      cin >> c;
      cin >> a >> b;
      if (c == 'A') {
        if (same(a, b)) {
          cout << "In the same gang." << endl;
        } else if (same(a, b+N)) {
          cout << "In different gangs." << endl;
        } else {
          cout << "Not sure yet" << endl;
        }
      } else if (c == 'D') {
        unite(a, b + N);
        unite(b, a + N);
      }
    }
  }
}
