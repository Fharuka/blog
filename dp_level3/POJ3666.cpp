/*
[http://poj.org/problem?id=3666:title]
長さNの数列が与えられる。
各項に数を加えたり減らしたりして、広義単調増加列または広義単調減少列にするための最小コストを求めよ。

***解法
数列のa[i]までの最小コスト

5, 6, 5, 7 -> 1
5, 6, 5, 7, 1 -> 5,5,5,5,1にするので3

増加列にする最小コストと減少列にする最小コストを別の配列で計算するか。
a[i]までの最小コストがわかっても、a[i]の値がいくつになるのかわからないよね
どうせわかるなら、各a[i]について
a[i]をいくつに変更したときの最小コストがわかるといいね
a[i]をb[i]に変えたときの最小コスト。。。でもb[i]の範囲がでかい。
座標圧縮すれば平気

増加列で考える
・座標圧縮してa[i]がたかだたN通りの値しか取らないようにする
・dp[i][j] = (a[i]を末尾とした部分列でa[i]を値jに変更してえの最小コスト)
・dp[i][j] = cost(a[i]to(j)) + min(dp[i-1][k] | k <= j)
・座標圧縮を考慮する

map
1000 => 3
100  => 2
10   => 1
1    => 0

圧縮座標を戻す方法は？
sort_a[i]を参照すればいい
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <utility>
#include <algorithm>
// #include <cstdlib>
using namespace std;
const int INF = 1000000000;
const int MAX_N = 2000;
int N;
vector<int> a, sort_a;
vector< vector<int> > dp;
multiset<int> m_sort_a;


// // 座標圧縮
// void compress() {
//   map<int, int> mp;
//
//   copy(a.begin(), a.end(), sort_a.begin());
//   sort(sort_a.begin(), sort_a.end());
//
//   int val = 0;
//   for (int i = 0; i < N; i++) {
//     mp.insert( make_pair(sort_a[i], i) );
//   }
//
//   for (int i = 0; i < N; i++) {
//     a[i] = mp[ a[i] ];
//   }
//   return;
// }

// 増加列と減少列で２回使う
int solve() {
  int _min;

  fill(dp[0].begin(), dp[0].end(), 0);
  // for (int j = 0; j < N; j++) {
  //   dp[0][j] = 0;
  // }
  // 増加列
  int i, j;
  for (i = 1; i <= N; i++) {
    _min = INF;
    for (j = 0; j < N; j++) {
      _min = min(_min, dp[i-1][j]);
      dp[i][j] = abs(a[i-1] - sort_a[j]) + _min;
    }
  }

  // 結果
  int res = INF;
  for (int i = 0; i < N; i++) {
    res = min(res, dp[N][i]);
  }
  return res;
}

int main() {
  // 入力
  cin >> N;
  a = vector<int>(N);
  dp = vector< vector<int> >(N+1, vector<int>(N));
  int tmp;
  for (int i = 0; i < N; i++) {
    scanf("%d", &tmp);
    a[i] = tmp;
    m_sort_a.insert(tmp);
  }

  // 座標圧縮
  // compress();

  // 座標圧縮じゃなくてこっちのほうがいいかもしれない
  sort_a = vector<int>(m_sort_a.begin(), m_sort_a.end());
  sort(sort_a.begin(), sort_a.end());


  // 確認
  // cout << "a" << endl;
  // for (int i = 0; i < N; i++) {
  //   cout << a[i] << endl;
  // }

  // 出力
  int res = solve();

  reverse(a.begin(), a.end());

  res = min(res, solve());

  cout << res << endl;
}
