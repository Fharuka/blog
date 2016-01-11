/*
ジョンはNドル持っていて、店には1ドル..Kドルの商品が無数にある。ちょうどNドルで商品を買う組み合わせは何通りあるか求めよ。
1 <= N <= 1000
1 <= K <= 100
5
= 1+1+1+1+1
= 1+1+1+2
= 1+2+2
= 1+1+3
= 2+3
5
= 1+4
6
= 1+1+1+1+1+1
= 1+1+1+1+2
= 1+1+2+2
= 1+1+1+3
= 1+2+3
= 2+2+2
= 3+3
7
= 1 + (6)
= 2+2+3
8
= 1 + (7)
= 2+2+2+2
= 2+3+3
dp[i][j] = (iドルで1..jドルの商品を買うときの組み合わせ)
dp[5][3] = 5
dp[5][4] = 6
dp[i][1] = 1
和の最大の数に着目すると、
dp[5][4] = dp[4][1] + dp[3][2] + dp[2][3] + dp[1][4]
dp[5][5] = dp[4][1] + dp[3][2] + dp[2][3] + dp[1][4] + dp[0][5]

dp[i][j] = dp[i-1][1] + dp[i-2][2] + dp[i-3][3] + ... + dp[i-j][j]
dp[i][j-1] = dp[i-1][1] + dp[i-2][2] + ... + dp[i-j+1][j-1]

dp[i][j] - dp[i][j-1] = dp[i-j][j]
dp[i][j] = dp[i][j-1] + dp[i-j][j]
dp[5][3] = dp[5][2] + dp[2][3]
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const unsigned long long MOD = 100000000000000000;
int main() {
  int N, K;
  cin >> N >> K;
  unsigned long long dp[1000+16][100+16][2];

  for (int j = 0; j <= K; j++) {
    dp[0][j][1] = 1;
    // dp[0][j][0] = 0;
  }
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= K; j++) {
      if (i >= j) {
        dp[i][j][0] = dp[i][j-1][0] + dp[i-j][j][0];
        dp[i][j][1] = dp[i][j-1][1] + dp[i-j][j][1];
        dp[i][j][0] += dp[i][j][1] / MOD;
        dp[i][j][1] = dp[i][j][1] % MOD;
      } else {
        dp[i][j][0] = dp[i][j-1][0];
        dp[i][j][1] = dp[i][j-1][1];
      }
    }
  }

  // for (int i = 0; i <= N; i++) {
  //   for (int j = 0; j <= K; j++) {
  //     cout << "所持金: " << i << " 商品1.." << j << " dp= " << dp[i][j] <<endl;
  //   }
  // }
  if (dp[N][K][0])
    cout << dp[N][K][0];
  cout << dp[N][K][1] << endl;
}
/*
100 100
190569292
500 100
2197282936549528745614
1000 100
15658181104580771094597751280645
600 100
419085883967052731637374
800 100
4575606410347783724917707119
*/
