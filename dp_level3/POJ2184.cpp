/*
N頭の牛それぞれに賢さs[i]と面白さf[i]が与えられている。
次の条件を満たす牛の部分集合を求め、TS+TFを出力せよ。
「TS >= 0 かつ TF >= 0 のもとでTS+TFが最大である」
1 <= N <= 100
-1000 <= s[i] <= 1000
-1000 <= f[i] <= 1000

dp[i][j][0/1] = (i番目までで、TS+TF=j(>=0)を実現した時のTSおよびTFの最大値)？？

s[i] >= 0 かつ f[i] >= 0 の牛は必ず入れることにする。
s[i] < 0 かつ f[i] < 0 の牛は必ず除くことにする。
s[i], f[i]のどちらか一方のみが正である牛だけを考えれば良い。

dp[i][j] = (i番目までで、TS=jのときのTFの最大値)

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
const int S_WIDTH = 200001;
const int S_HALF = 100000;

int main() {
  // ifstream cin("test.txt");
  int n;
  vector<int> s;
  vector<int> f;
  cin >> n;
  int _s, _f, add_to_res = 0;
  while(n--) {
    cin >> _s >> _f;
    if (_s <= 0 && _f <= 0) {
      continue;
    } else if (_s >= 0 && _f >= 0) {
      add_to_res += _s + _f;
    } else {
      s.push_back(_s);
      f.push_back(_f);
    }
  }
  int m = s.size();

  // dp[i][j] = (i番目までで、TS=jのときのTFの最大値)
  // TS < 0 もありうるので、TS = j - 100000 としよう
  vector<int> dp(S_WIDTH, -INF);
  dp[ S_HALF ] = 0;
  for (int i = 0; i < m; i++) {
    if (s[i] < 0) {
      for (int j = 1000; j < S_WIDTH - 1000; j++) {
        // if (dp[j-s[i]] != -INF)
          dp[j] = max(dp[j], dp[ j - s[i] ] + f[i]);
        // 表示
        // if (dp[j] > -100) {
        //   cout << i << " " << j - S_HALF << " " << dp[j] << endl;
        // }
      }
    } else {
      for (int j = S_WIDTH - 1000; j >= 1000; j--) {
        // if (dp[j-s[i]] != -INF)
          dp[j] = max(dp[j], dp[ j - s[i] ] + f[i]);
        // 表示
        // if (dp[j] > -100) {
        //   cout << i << " " << j - S_HALF << " " << dp[j] << endl;
        // }
      }
    }
  }

  int res = 0;
  for (int j = S_HALF; j < S_WIDTH; j++) {
    if (dp[j] >= 0)
      res = max(res, j - S_HALF + dp[j]);
    // if (res == 50003) {
    //   cout << j - S_HALF << " " << dp[j] << endl;
    //   break;
    // }
  }
  res += add_to_res;
  cout << res << endl;

}
