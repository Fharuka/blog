/*
毎分、2本の木のどちらかからりんごが落ちる。ベシーは毎分、どちらかのりんごの木の下にいて、落ちてくるりんごをキャッチできる。ベシーが2本の木の間を移動する回数は最大でW回(1 <= W <= 30)。りんごはT分間(1 <= T <= 1000)落ちる。毎分、どの木からりんごが落ちるかデータが与えられたときに、ベシーがキャッチできるりんごの最大数を求めよ。最初、ベシーは木1にいる。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

// j回移動したあとにtree(1 or 2)が来たらりんごをゲットできるかどうか
// 奇数回移動したらtree2でゲット。偶数回移動したらtree1でゲット
int func(int j, int tree) {
  if (j % 2 == tree - 1) {
    return 1;
  } else {
    return 0;
  }
}

int main() {
  // 入力
  int T,W;
  cin >> T >> W;
  W = min(W, T); // T回より多く移動できないから
  vector<int> tree(T+1);
  for (int i = 1; i <= T; i++) {
    scanf("%d", &tree[i]);
  }
  // 動的計画法
  // dp[i][j] : i分までにj回移動したときに得られるりんごの最大数
  vector< vector<int> > dp(T+1, vector<int>(W+1));
  // j = 0
  dp[1][0] = (tree[1] == 1) ? 1 : 0;
  for (int i = 1; i < T; i++) {
    dp[i+1][0] = dp[i][0] + func(0, tree[i+1]);
    // cout << "dp " << i+1 << " 0 = " << dp[i+1][0] << endl;
  }
  // j > 0
  for (int j = 1; j <= W; j++) {
    // j回移動する場合のスタートはj分
    if (j == 1) {
      dp[1][1] = 1 - dp[1][0];
    } else {
      dp[j][j] = dp[j-1][j-1] + func(j, tree[j]);
    }
    for (int i = j; i < T; i++) {
      dp[i+1][j] = max(
        dp[i][j] + func(j, tree[i+1]),  // 移動するタイミングを変えない
        dp[i][j-1] + func(j, tree[i+1]) // 移動のうち1回を最後のi+1分にずらした
      );
      // cout << "dp " << i+1 << " " << j << " = " << dp[i+1][j] << endl;
    }
  }

  // dp[T-1][j]の中で最大値が答え
  int res = 0;
  for (int j = 0; j <= W; j++) {
    res = max(res, dp[T][j]);
  }

  // 出力
  cout << res << endl;
}
/*
1 2
 1[i] 2[i]
2 8 9
2 8 8
2 8 7
2 8 6
2 8 5
1 8 4
2 7 4
1 7 5
1 6 5
2 5 5
1 5 4
1 4 4
2 3 4
2 3 3
2 3 2
1 3 1
2 2 1
1 2 0
1 1 0

1[i] > 2[i]
なら 1 にいたほうがよい
1[i] < 2[i]
なら 2 にいたほうがよい
dp[i][j][k] =
i分までにj回以下の移動回数で木kの下にいるときに取れるりんごの最大数
or
dp[i][j]
i分までにj回の移動回数で取れるりんごの最大数
j回移動したらjの偶奇によって最終ポジションが分かる
dp[i+1][j] = dp[i][j] + (tree[i+1] == (jの最終ポジション))
dp[i][j+1] = ??

dp[i+1][j] = max(dp[i][j] + (1 or 0), dp[i][j-1] + (1 or 0))

3回ジャンプで検証
1 j 2
1 j 1 +
1 j 2
sum=1
1   1 +
1 j 2
1 j 1 +
2 j 2 +
sum = 3
*/
