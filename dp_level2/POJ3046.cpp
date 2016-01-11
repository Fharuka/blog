/*
T種類の蟻の家族がいて、蟻の家族内では個々の蟻の区別はない。蟻の家族iにはN[i]匹の蟻がいる。全家族を合わせると蟻は合計A匹である。サイズがS以上B以下の蟻のグループが何個作れるかを計算せよ。
1 <= T <= 1000
1 <= Ni <= 100
1 <= S <= B <= A <= 100000

***解法
dp[i][j] = i番目までのファミリーでサイズjの集合が作れる個数
// d[i-1][j] > 0のとき、i-1番目までのファミリーでサイズjの集合が作れている
dp[i+1][j] = dp[i][j] + dp[i][j-1] + ... + dp[i][j-m]
// ただし m = min(j, N[i])
// けどこれは効率が悪いので式変形で工夫
// 和で定義される数列を簡単な漸化式にする方法と同じ
dp[i+1][j]   = dp[i][j] + dp[i][j-1] + ... + dp[i][j-m(j)]
dp[i+1][j-1] = dp[i][j-1] + dp[i][j-2] + ... + dp[i][j-m(j-1)]
両辺を引いて
dp[i+1][j] - dp[i+1][j-1] = dp[i][j] (- dp[i][j-N[i]-1])
dp[i+1][j] = dp[i+1][j-1] + dp[i][j] (- dp[i][j-N[i]-1])
最後の項はj-N[i]-1 < 0のときには存在しない。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int MOD = 1000000;

int main() {
  // 入力
  // ifstream cin( "test.txt" );
  int t, a, s, b;
  cin >> t >> a >> s >> b;
  int n;
  int N[1001] = {0};
  for (int i = 0; i < a; i++) {
    // cin >> n;
    scanf("%d", &n);
    N[n]++;
  }
  // 計算
  vector< vector<int> > dp(2, vector<int>(b+1));
  dp[0][0] = 1;
  dp[1][0] = 1;
  for (int j = 1; j <= b; j++) {
    dp[1][j] = (j <= N[1]) ? 1 : 0;
  }
  for (int i = 1; i < t; i++) {
    for (int j = 1; j <= b; j++) {
      int k = (i + 1) % 2;
      int l = i % 2;
      if (j - N[i+1] - 1 >= 0) {
        dp[k][j] = (dp[k][j-1] + dp[l][j] - dp[l][j-N[i+1]-1] + MOD) % MOD;
      } else {
        dp[k][j] = (dp[k][j-1] + dp[l][j]) % MOD;
      }
    }
  }

  int sum = 0;
  for (int i = s; i <= b; i++) {
    sum += dp[t%2][i];
    sum %= MOD;
  }

  // 出力
  cout << sum << endl;
}
