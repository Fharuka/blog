/*
[http://poj.org/problem?id=3280:title]
***問題概要
N種類のアルファベットからなる長さMの文字列が与えられる。
文字列に文字を追加したり削除したりして、回文にしたい。文字の追加も削除も任意の位置に行える。文字の追加と削除には文字の種類ごとにコストがかかる。追加と削除のコストは別に与えられる。文字列を回文にするのにかかる最小コストを求めよ。
1 <= M <= 2,000
1 <= N <= 26
0 <= cost <= 10,000
***解法
dp[i][j] : [i,j)を修正して回文にする最小コスト
https://eagletmt.github.io/contests/blog/poj-3280/
----
dp[i][i] = dp[i][i+1] = 0 (長さが 0, 1 の文字列は回文)
dp[i-1][j] := dp[i][j] + cost[i-1 番目の文字] (区間を左側にのばす)
dp[i][j+1] := dp[i][j] + cost[j 番目の文字] (区間を右側にのばす)
dp[i-1][j+1] := dp[i][j]  (i-1 番目の文字と j 番目の文字が等しいとき、コスト無しで区間を両側にのばす)
----
(文字数Mの文字列を回文にする最小コスト)
= min(
  (左1文字を除いた文字数M-1の文字列の最小コスト) + cost(左1文字),
  (右1文字を除いた文字数M-1の文字列の最小コスト) + cost(右1文字),
  (もし左右の文字が同じなら左右の1文字ずつを除いた文字数M-2の文字列の最小コスト)
);
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

int main() {
  // ifstream cin( "test.txt" );
  // 入力
  int N, M;
  cin >> N >> M;
  char str[2000];
  cin >> str;
  int cost[26];
  char c;
  int a, d;
  for (int i = 0; i < N; i++) {
    cin >> c >> a >> d;
    cost[c - 'a'] = min(a,d);
  }
  // 動的計画法
  vector< vector<int> > dp(M, vector<int>(M+1, INF));
  for (int i = 0; i < M; i++) {
    dp[i][i]   = 0;
    dp[i][i+1] = 0;
  }
  for (int l = 2; l <= M; l++) {
    for (int i = 0; i + l <= M; i++) {
      dp[i][i+l] = min(dp[i][i+l-1] + cost[str[i+l-1] - 'a'],dp[i+1][i+l] + cost[str[i] - 'a']);
      if (str[i] == str[i+l-1]) {
        dp[i][i+l] = min(dp[i][i+l], dp[i+1][i+l-1]);
      }
    }
  }
  // 出力
  cout << dp[0][M] << endl;
}
