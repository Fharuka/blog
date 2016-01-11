/*
h a c
7 40 3
5 23 8
2 52 6
5 * 3
15
7*3
36
2*6
48

ブロックをa順にソートする
i番目までのブロック、j in (a[i]-99)..a[i]の高さが作れるか否か、、、
しかしこのjの作り方には問題がある。a[i]-99以下の高さまでしか積めない場合無理だってことと、ブール値を使った動的計画法だからきっと無駄があるってことだ。
個数制限付き動的計画法の考え方を使おう。
dp[i][j] = (i番目までで高さjを作るとa[i]が何個あまるか)

ひさしぶりに一発Accepted!!

個数制限付き部分和問題
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int MAX_A = 40001;
struct block {
  int h, a, c;
  bool operator<( const block& other ) const {
    return a < other.a;
  }
};

int main() {
  // ifstream cin( "test.txt" );
  // 入力
  int n, _n;
  vector< block > b;
  int h, a, c;
  cin >> n;
  _n = n;
  while (_n--) {
    cin >> h >> a >> c;
    block bl = {h, a, c};
    b.push_back(bl);
  }
  sort(b.begin(), b.end());

  // dp[i][j] = (i番目までで高さjを作るとa[i]が何個あまるか)
  int dp[MAX_A];
  fill(dp, dp + MAX_A, -1);
  dp[0] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < MAX_A; j++) {
      if (j > b[i].a) {
        continue;
      }

      if (dp[j] >= 0) {
        dp[j] = b[i].c;
      } else if (j - b[i].h >= 0 && dp[ j - b[i].h ] > 0) {
        dp[j] = dp[ j - b[i].h ] - 1;
      } else {
        dp[j] = -1;
      }
    }
  }

  int res = 0;
  for (int i = 0; i < MAX_A; i++) {
    res = (dp[i] >= 0) ? i : res;
  }

  cout << res << endl;
}
