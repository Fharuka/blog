/*
[http://poj.org/problem?id=2139:title]
**問題概要
N頭の牛がいて、映画の「共演距離」を考える。まず、自分自身との共演距離は0である。ひとつの映画で牛iと牛jが共演していたら、牛iと牛jの共演距離は1である。また、牛iと牛jがどの映画でも共演していないが、牛iと牛kがひとつの映画で共演していて、牛kと牛jが別の映画で共演していれば、共演距離は2である。共演距離3,4,...も同様に定める。
ほかの牛たちとの共演距離の平均が最小となる牛について、その平均を100倍した整数を出力せよ。
2 <= N <= 300
1 <= M <= 10000 (Mは映画の個数)
**解法
ワーシャルフロイド法。N^3 = 27,000,000 なのでO(N^3)で間に合う。
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
const int MAX_N = 300;

int main() {
  // ifstream cin("../test.txt");
  // 入力
  int N, M, i, j, k;
  cin >> N >> M;
  // dpの初期化
  int dp[MAX_N][MAX_N];
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (i == j) {
        dp[i][i] = 0;
      } else {
        dp[i][j] = INF;
      }
    }
  }
  // 共演距離1
  int movie[MAX_N];
  int cows;
  while (M--) {
    cin >> cows;
    for (i = 0; i < cows; i++) {
      cin >> movie[i];
    }
    for (i = 0; i < cows - 1; i++) {
      for (j = i + 1; j < cows; j++) {
        dp[movie[i] - 1][movie[j] - 1] = 1;
        dp[movie[j] - 1][movie[i] - 1] = 1;
      }
    }
  }
  // ワーシャルフロイド
  for (k = 0; k < N; k++) {
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        if (dp[i][j] > dp[i][k] + dp[k][j])
          dp[i][j] = dp[i][k] + dp[k][j];
      }
    }
  }
  // 各牛について平均距離の計算
  float mean[MAX_N];
  for (i = 0; i < N; i++) {
    mean[i] = 0;
    for (j = 0; j < N; j++) {
      // cout << dp[i][j] << endl;
      mean[i] += dp[i][j];
    }
    mean[i] /= N - 1;
    mean[i] *= 100;
  }
  // 最小の平均を出力
  int ans = INF;
  for (i = 0; i < N; i++) {
    ans = min(ans, (int)mean[i]);
  }
  cout << ans << endl;
}
