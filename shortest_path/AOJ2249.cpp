/*
*AOJ2249: Road Construction
[http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2249:title]
**問題概要
N(1 <= N <= 10000)個の町がある。ひとつは首都である。町々をつなぐ道路を建設する計画があったが、コストがかかりすぎるので、最初の計画からいくつか道路を除外して、新たな道路建設計画を立てることにした。そのとき、次の条件を満たすようにしたい。
・どの2つの町も、それらをつなぐ経路が存在する。
・首都から各町への最短距離は最初の計画から変わらないようにする。
これらの条件を満たす計画のうち、コストが最小となる計画のコストを出力せよ。与えられる道路の情報はM(1 <= M <= 20000)個。道路の情報は、どの町とどの町をつなぐかだけでなく、距離とコストが与えられる。
**解法
首都から各町への最短距離は、負の経路を持たない単一終点最短経路問題なので、ダイクストラ法でいける。最短経路が複数ある場合には、首都に向かっていく最初に進む辺にかかるコストが最小のものを選ぶ。町iからの最短経路の求め方は、d[i] = d[j] + cost[i][j]を満たす町jが、最短経路上にある町となる。
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
const int MAX_N = 10000;
struct edge{int to, dist, cost;};

int main() {
  // ifstream cin("../test.txt");
  while (true) {
    // 入力
    int N, M;
    cin >> N >> M;
    if (!(N | M)) break;
    vector<edge> roads[MAX_N];
    int u, v, t, c;
    while (M--) {
      cin >> u >> v >> t >> c;
      u--; v--;
      edge e1 = {v, t, c};
      edge e2 = {u, t, c};
      roads[u].push_back(e1);
      roads[v].push_back(e2);
    }

    int d[MAX_N];
    fill(d, d + N, INF);
    d[0] = 0;
    // P(最短距離、頂点)
    priority_queue<P, vector<P>, greater<P> > qu;
    qu.push(P(0,0));
    // ダイクストラ
    while (!qu.empty()) {
      P p = qu.top();
      qu.pop();
      int v = p.second;
      if (d[v] < p.first) continue;
      for (int i = 0; i < roads[v].size(); i++) {
        edge e = roads[v][i];
        if (d[e.to] > d[v] + e.dist) {
          d[e.to] = d[v] + e.dist;
          qu.push(P(d[e.to], e.to));
        }
      }
    }

    //距離表示
    // cout << "----------" << endl;
    // for (int i = 0; i < N; i++) {
    //   cout << i << " " << d[i] << endl;
    // }

    // コスト最小の経路を探して、コストの和の最小値を求める
    int min_total = 0;
    for (int v = 1 ; v < N; v++) {
      int min_cost = INF;
      for (int i = 0; i < roads[v].size(); i++) {
        edge e = roads[v][i];
        if (d[v] == d[e.to] + e.dist && e.cost < min_cost)
          min_cost = e.cost;
      }
      min_total += min_cost;
    }

    // 出力
    cout << min_total << endl;
  }
}
