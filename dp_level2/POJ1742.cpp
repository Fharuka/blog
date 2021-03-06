/*
http://poj.org/problem?id=1742
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

int main() {
  int n, m;
  int a[100];
  int c[100];
  int dp[100001];
  int cnt;
  // ifstream cin( "test.txt" );
  while (1) {
    // 入力
    cin >> n >> m;
    if (!(n | m)) return 0;

    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = 0; i < n; i++)
      cin >> c[i];

    // 計算
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= m; j++) {
        if (dp[j] >= 0) {
          dp[j] = c[i];
        } else if ( j - a[i] >= 0 && dp[j-a[i]] > 0) {
          dp[j] = dp[j - a[i]] - 1;
        } else {
          dp[j] = -1;
        }
      }
    }
    cnt = 0;
    for (int j = 1; j <= m; j++) {
      if (dp[j] >= 0) cnt++;
    }
    // 出力
    cout << cnt << endl;
  }
}

個数制限付き部分和問題
POJ1742を解こうとしたが、蟻本P.62の「個数制限付き部分和問題」とほぼ同じだった。
この問題の漸化式の作り方が難しかったので、ここで整理しておく。

以下、蟻本P.62-63を参考に書いた。

個数制限付き部分和問題
n種類の数a[i]がそれぞれm[i]個ずつある。この中からいくつか選び、その総和をちょうどKにできるかどうかを判定せよ。
制約
1 <= n <= 100
1 <= a[i], m[i] <= 100,000
1 <= K <= 100,000
例
n = 3
a = {3, 5, 8}
m = {3, 2, 2}
K = 17

例を使ってしばらく遊んでみる。
使える数は 3, 5, 8 で、
数 3 : 3個
数 5 : 2個
数 8 : 2個
というわけだ。全部並べると、
3, 3, 3, 5, 5, 8, 8
これで指定された数Kが作れるか？

K = 17 だけでなく、K = 1から順に見てみよう。

K  : 作れるかどうか(作れないならx)
1  : x
2  : x
3  = 3
4  : x
5  = 5
6  = 3 + 3
7  : x
8  = 3 + 5 = 8
9  = 3 + 3 + 3
10 = 5 + 5
11 = 3 + 3 + 5
12 : x
13 = 3 + 5 + 5 = 5 + 8
14 = 3 + 3 + 8
15 : x
16 = 3 + 3 + 5 + 5 = 3 + 5 + 8 = 8 + 8
17 = 3 + 3 + 3 + 8

さて、観察する。
ある数Kが作れるとき、どんな状況になっているか。
K = 17 = 3 + 3 + 3 + 8 だが、これは
K = 9 のときに和が作れているからだ。
つまり、
17 = (9を和にした式) + 8
という形だ。

一般化しよう。
n種類の数　a[0], a[1], ... a[n-1] に対して a[0],...,a[i]を「i番目までの数のグループ」と呼ぼう。
さてi番目までの数のグループを使ってjが作れるとしたら、
次の事実が成り立つ。
「i-1番目までの数のグループを使って、j, j-a[i], j-2*a[i], ..., j-m[i]*a[i] のうちの少なくとも一つを作れる。」

bool値によるdpを次のように定義しよう。
dp[i][j] = (i番目までの数のグループを使って数jを作れるかどうか)
もちろん、数jを作れるならtrue, 作れないならfalseである。
すると、先の考察から漸化式ができる。

dp[i][j] = dp[i-1][j] || dp[i-1][j-a[i]] || ... || dp[i-1][j-m[i]*a[i]]

ただ、この漸化式は修正しなければならない。j-m[i]*a[i] < 0 になるかもしれないから。
修正すると、整数kを j - k * a[i] >= 0 かつ k <= m[i] を満たす最大の整数として、

dp[i][j] = dp[i-1][j] || dp[i-1][j-a[i]] || ... || dp[i-1][j-k*a[i]]

となる。

以上がブール値による動的計画法である。が、蟻本によるとブール値による動的計画法は効率が悪いことが多いそうだ。dpにもっと情報を盛り込むことで効率の良い動的計画法になる。

上のブール値によるdpの漸化式では、dp[i][j]を1つ計算するのに最大でm[i]+1個の値を参照しなければならない。これをもっと減らせるようにdpの定義を工夫しよう。
漸化式を観察して気づくのは、次の事実だ。
「i番目までの数のグループを使って数jを作れたとして、その和が
  (i-1番目までの数のグループを使った和) + k * a[i]   (k > 0)
  という形になるならば、i番目までの数のグループを使って数j-a[i]が作れる。」
この事実からわかるのは、i番目までの数のグループを使って数jを作れるかどうかを知りたいなら、i番目までの数のグループを使って数j-a[i]を作れるかどうか（そして作れたとしたらa[i]が少なくとも1個余っているかどうか）を調べればよいということだ。この考え方なら参照する要素を減らせそうだ。

そこでdpの定義を
dp[i][j] = (i番目までの数のグループを使って数jを作った時にa[i]が最大何個余るか)
にする。数jを作れないときには dp[i][j] = -1 とする。
すると、うまいこと漸化式を作れる。場合分けしよう。

(1) すでにi-1番目までの数のグループを使って数jを作れるとき:
    数a[i]は1個も使わなくてよいので、 dp[i][j] = m[i]
(2) 場合(1)でなく、i番目までの数のグループでj-a[i]を作れて、a[i]が1個以上あまるとき:
    a[i]を1個加えればjになるので、 dp[i][j] = dp[i][j-a[i]] - 1
(3) 場合(1)でも(2)でもないとき:
    dp[i][j] = -1

これはコードで書くと以下のようになる。
>|cpp|
if (dp[i-1][j] >= 0) {
  dp[i][j] = m[i];
} else if (j - a[i] >= 0 && dp[i][j-a[i]] > 0) {
  dp[i][j] = dp[i][j-a[i]] - 1;
} else {
  dp[i][j] = -1;
}
||<

これでオッケーだが、この問題の場合はdp[100][100000]を作ると配列のサイズが大きすぎるので、配列の再利用をしてdp[100000]で計算する。

最後に、おまけでPOJ1742のコード。
>|cpp|

||<
