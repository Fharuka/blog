/*
[http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0189:title]
解法
全点対最短経路問題。
町の数が10以下なので、ワーシャルフロイドの計算時間O(V^3)で通る。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int INF = 1000000;
const int N = 10;

int main() {
  // ifstream cin("../test.txt");
  int n;
  while (true) {
    cin >> n;
    if (!n) break;
    int dp[N][N];
    // 初期化
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        dp[i][j] = INF; // i=jは？
      }
    }
    int a, b, c;
    while (n--) {
      cin >> a >> b >> c;
      dp[a][b] = c;
      dp[b][a] = c;
    }
    // ワーシャルフロイド法
    for (int k = 0; k < N; k++) {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          if (dp[i][j] > dp[i][k] + dp[k][j])
            dp[i][j] = dp[i][k] + dp[k][j];
        }
      }
    }
    // 町ごとに通勤時間の総和を計算
    int sum[N];
    for (int i = 0; i < N; i++) {
      sum[i] = 0;
      for (int j = 0; j < N; j++) {
        if (i != j && dp[i][j] != INF) {
          sum[i] += dp[i][j];
        }
      }
    }
    // 通勤時間が最小の町を求める
    int ans_i = 0;
    for (int i = 1; i < N; i++) {
      if (sum[i] < sum[ans_i] && sum[i] != 0)
        ans_i = i;
    }
    // 出力
    cout << ans_i << " " << sum[ans_i] << endl;
  }
}
