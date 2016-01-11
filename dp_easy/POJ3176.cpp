/*
0以上99以下の数字を使ってボーリングをする
例 5列のピン
     7
    3 8
   8 1 6
  2 8 4 4
 4 5 2 6 5
牛がこのピンを通過する。トップから始めて、下の二つの数のどちらかに下っていき、一番下の列まで行く。通過した数字の合計がその牛の点数となる。N (1 <= N <= 350) 350)列のピンが与えられるので、可能な点数の最大値を求めよ。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

int main() {
  // 入力
  int N;
  cin >> N;
  vector< vector<int> >  pin(N, vector<int>(N) );
  vector< vector<int> >  dp(N, vector<int>(N) );
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= i; j++) {
      cin >> pin[i][j];
    }
  }
  // 動的計画法。ボトムアップ
  for (int j = 0; j < N; j++) {
    dp[N-1][j] = pin[N-1][j];
  }
  if (N == 1) {
    cout << dp[0][0] << endl;
    return 0;
  }
  // N >= 2
  for (int i = N - 2; i >= 0; i--) {
    for (int j = 0; j <= i; j++) {
      dp[i][j] = pin[i][j] + max(dp[i+1][j], dp[i+1][j+1]);
    }
  }

  // 出力
  cout << dp[0][0] << endl;
}
