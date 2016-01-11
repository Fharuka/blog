/*
[http://poj.org/problem?id=1631:title]
蟻本P.63そのもの
最長増加部分裂問題(実際には最長減少部分列をも求める)
長さに対する最小の最終要素をdpで計算する
dp[i] = (長さがi+1であるような部分増加列における最終要素の最小値)
存在しない場合はd[i] = INF

4
2
6
3
1
7

4を見る
dp[0] = 4

2を見る
dp[0] = 2

6を見る
dp[0] = 2
dp[1] = 6

3を見る
dp[0] = 2
dp[1] = 3

1を見る
dp[0] = 2
dp[1] = 3

7を見る
dp[0] = 2
dp[1] = 3
dp[2] = 7

a[j]に対して、a[j] <= dp[i]なる最小のiを探せばいいので、dp内を二分探索

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
const int N = 40000;

int main() {
  // 入力
  int testcase, p, a[N], dp[N], res;
  scanf("%d", &testcase);
  while (testcase--) {
    scanf("%d", &p);
    for (int i = 0; i < p; i++) {
      scanf("%d", &a[i]);
    }

    // 最長増加部分列
    fill(dp, dp + N, INF);
    for (int i = 0; i < p; i++) {
      *lower_bound(dp, dp + p, a[i]) = a[i];
    }

    res = lower_bound(dp, dp + p, INF) - dp;

    cout << res << endl;
  }
}
