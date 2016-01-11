/*
*POJ3045: Cow Acrobats
[http://poj.org/problem?id=3045:title]
**問題概要
N 頭の牛が垂直に重なってタワーを作る。牛 i には重さ W[i] と強さ S[i] がある。牛 i の危険度は、 (上に乗っている牛の重さの和) - (牛 i の強さ) で計算される。牛の危険度の最大値を最小化せよ。
**解法
危険度の最大値が x 以下、つまりすべての牛の危険度を x 以下にできるかどうかの判定 C(x) は、O(N log N) でできる。次のように考えればよい。それぞれの牛 i について、危険度が x 以下であるなら、
(上に乗れる牛の重さの和) <= (牛 i の強さ) + x
が成立する。
牛を下から積み上げることにする。牛を強い順に見ていきその位置の重さにたえられる牛をまずは集める。そして、「その位置の重さにたえられる牛の中で体重の最も大きな牛を配置する」というルールで順に牛を配置する。これで  C(x) が判定できる。あとは C(x) を満たす x のうち最小の値を二分探索で求める。
>|cpp|
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int INF = 1010000000;
vector<pair<int, int> > cow;
int N;
int sum_w;

//------- 条件 C(x) を満たす最小の x を求める二分探索
// 条件を満たすかどうかの関数
bool C(int x) {
  priority_queue<int> que;
  int sum = sum_w;
  int w, s;
  for (int i = 0; i < N; i++) {
    s = cow[i].first;
    w = cow[i].second;
    while (sum > s + x) {
      if (que.empty()) return false;
      sum -= que.top();
      que.pop();
    }
    que.push(w);
  }
  return true;
}

// 二分探索
int bi_search() {
  int lb = -INF, ub = INF;

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
  cin >> N;
  cow = vector<pair<int, int> >(N);
  sum_w = 0;
  int w, s;
  for (int i = 0; i < N; i++) {
    cin >> w >> s;
    cow[i] = make_pair(s + w, w);
    sum_w += w;
  }
  sort(cow.begin(), cow.end());
  reverse(cow.begin(), cow.end());

  int res = bi_search();

  cout << res << endl;
}
