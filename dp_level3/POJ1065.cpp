/*
(a) The setup time for the first wooden stick is 1 minute.
(b) Right after processing a stick of length l and weight w , the machine will need no setup time for a stick of length l' and weight w' if l <= l' and w <= w'. Otherwise, it will need 1 minute for setup.
(a) 最初の棒のセットアップは1分
(b) 前の棒が(l,w)で次の棒が(l',w')とする。
if i <= l' && w <= w'
  0 minute
else
  1 minute
end
まずは単純化して長さlだけの問題を考えよう。
明らかに長さの小さい順にソートすれば、setup時間は1分ですむ。
長さと重さの問題だ。
長さの小さい順にソートしておく。
dp[i] = (棒iまでのsetup時間)
dp[i+1] =
if ( (w,l) <= (nw,nl) <= (w',l')となる棒がある)
  dp[i]
else
  dp[i] + 1
end
でも枝の先だったらまた条件が違ってくるな。

dp[i][j] = (i番目まででsettime最小になる並べ方の末端の数字の最小値)
dp[i+1][j] =
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <set>
using namespace std;

int main() {
  // 入力
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    vector< pair<int,int> > lw(n);
    int l, w;
    for (int i = 0; i < n; i++) {
      scanf("%d%d", &l, &w);
      lw[i] = make_pair(l,w);
    }
    sort(lw.begin(), lw.end());
    // 計算
    multiset<int> ter; // 末端の集合
    multiset<int>::iterator it;
    for (int i = 0; i < n; i++) {
      // w <= new_w なる末端のうち最大のものを探す
      // new_w < w なる最初のwの一個手前
      it = ter.upper_bound(lw[i].second);
      if (it == ter.begin()) {
        ter.insert(lw[i].second);
      } else {
        ter.erase(--it);
        ter.insert(lw[i].second);
      }
    }
    // 出力
    cout << ter.size() << endl;
  }
}
