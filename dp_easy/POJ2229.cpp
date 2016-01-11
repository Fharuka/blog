/*
整数Nを2のべき乗にによって表される整数(1,2,4,8,16,...)の和で表すのは何通りが可能か。
1 <= N <= 1000000
整数mがdp(m)通りの和で表せるとすると、
整数m+1はdp(m) + dp(m - 1) + dp()
1:
1
2:
1+1
2
3: dp[2]
1+1+1
1+2
4: dp[3] + dp[2]
1+1+1+1
1+1+2
2+2
4
5: dp[4]
1+1+1+1+1
1+1+1+2
1+2+2
1+4
6
1 + dp[5]
2+2+2 = 2 * (1+1+1)
2+4 = 2 * (1+2)
dp[6] = dp[5] + dp[3]

dp[12]
dp[11] + dp[6]
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int MAX = 1000000000;

int main() {
  int N;
  cin >> N;
  vector<unsigned long long> dp(N);
  dp[1] = 1;
  for (int i = 2; i <= N; i++) {
    // 偶奇で場合分け
    dp[i] = (i % 2 == 0) ? dp[i-1] + dp[i/2] : dp[i-1];
    dp[i] %= MAX;
  }
  cout << dp[N] << endl;
}
