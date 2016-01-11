/*
[http://poj.org/problem?id=3616:title]
***問題概要
牛がN時間ミルクを出す。ジョンは搾乳可能な時間帯のリストを持っている。リストはM個の期間からなり、期間の重複があり得る。各期間iにはそれぞれ開始時間starting_our(i)、終了時間ending_hour(i)、その期間に牛から搾乳できるミルクの量efficiency(i)が与えられている。牛は搾乳期間の間ミルクを出すが、期間が終わると時間Rの休憩を入れなければならない。牛から搾乳できるミルクの最大量を求めよ。
1 <= N <= 1,000,000
1 <= M <= 1,000
0 <= starting_our(i) < ending_hour(i) <= N
1 <= efficiency(i) <= 1,000,000
1 <= R <= N
***解法
搾乳期間のリストを開始時間の小さい順にソートする。
dp[i]を搾乳期間i番目以降の期間から選んだときの最大ミルク量として漸化式を作る。dp[0]が答えになる。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
// 搾乳期間を構造体で定義
struct Interval {
  int s, e, effi; // starting_our, ending_hour+R, efficiency
  bool operator<(const Interval& another) const {
    return s < another.s;
  }
};

int main() {
  // 入力
  // ifstream cin( "test.txt" );
  int N, M, R;
  cin >> N >> M >> R;
  vector<Interval> v(M);
  for (int i = 0; i < M; i++) {
    cin >> v[i].s >> v[i].e >> v[i].effi;
    v[i].e += R;
  }
  // 開始時間の早い順にソート
  sort(v.begin(), v.end());

  // 計算
  vector<int> dp(M+1);
  int j, comp;
  dp[M] = 0;
  dp[M-1] = v[M-1].effi;
  for (int i = M-2; i >= 0; i--) {
    // 開始時間がv[i].e以降の最初の期間を検索する
    j = i+1;
    while (j < M) {
      if (v[i].e <= v[j].s) {
        break;
      }
      j++;
    }
    // 検索した値jをもとに漸化式で比較すべき値を求める
    comp = dp[j];
    // 漸化式
    dp[i] = max(dp[i+1], v[i].effi + comp);
  }

  // 出力
  cout << dp[0] << endl;
}
/*
*** *** *** ***
 *R R           8
             ** 19
    *** RR      24
         ** *RR 31

---------------
    *** RR   ** 43

i番目までの期間、時間jまでの最大ミルク量dp[i][j]。
dp[i+1][j] = max(dp[i][j])
*/
