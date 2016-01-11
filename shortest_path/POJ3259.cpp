/*
ベルマンフォードって「更新できる辺を更新する」ってだけの辺ループなんだな
**問題概要
負の辺が存在するグラフで、負の閉路が存在するなら"YES"を、存在しないなら"NO"を出力させる問題。
**解法
ベルマンフォード法。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int INF = 1000000000;
const int MAX_N = 500;
struct edge {int from, to, cost;};

int main() {
  // ifstream cin("../test.txt");
  int F, N, M, W;
  cin >> F;
  int d[MAX_N];
  while (F--) {
    vector<edge> es;
    cin >> N >> M >> W;
    fill(d, d + N, INF);
    d[0] = 0;
    // 辺の入力
    int f,t,c;
    for (int i = 0; i < M; i++) {
      cin >> f >> t >> c;
      edge p1 = {f-1, t-1, c};
      edge p2 = {t-1, f-1, c};
      es.push_back(p1);
      es.push_back(p2);
    }
    for (int i = 0; i < W; i++) {
      cin >> f >> t >> c;
      edge wh = {f-1, t-1, -c};
      es.push_back(wh);
    }
    // ベルマンフォード。辺についてのループ
    int m = es.size();
    while (true) {
      bool flag = false;
      for (int i = 0; i < m; i++) {
        edge e = es[i];
        if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
          d[e.to] = d[e.from] + e.cost;
          flag = true;
        }
      }
      if (!flag || d[0] < 0) break;
    }
    // // 表示
    // for (int i = 0; i < 3; i++)
    //   cout << d[i] <<endl;
    // 出力
    if (d[0] >= 0) {
      cout << "NO" << endl;
    } else {
      cout << "YES" << endl;
    }
  }
}
