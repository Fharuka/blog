/*
ジョンはN頭の牛を放牧している。ジョンが戻ったとき、数頭の牛が庭に入って花を食べていた。続くダメージを最小にするため、ジョンはすぐに牛を小屋に戻すことにした。
牛iは小屋からTi分の場所にいる。さらに、移動を待っている間、1分当たりDiの花を食べる。ジョンは一度に1頭の牛しか移動させられない。牛iを移動させ終えるのに2 * Ti分かかる。ある牛を移動させてから別の牛を移動させるまでに余分の時間はかからない。破壊される花が最小に食い止められるように牛を順番に移動させるプログラムをかけ。
2 <= N <= 100000
1 <= Ti <= 2000000
1 <= Di <= 100
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
struct Cow {
  int d,t;
  // この比較がキモである
  bool operator<(const Cow& another) const {
     return t * another.d < d * another.t;
  }
};

int main() {
  // 入力
  int n;
  cin >> n;
  vector<Cow> cows(n);
  int t,d;
  long long dsum = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &t, &d);
    cows[i].t = 2 * t;
    cows[i].d = d;
    dsum += d;
  }

  // 貪欲法のためのソート
  sort(cows.begin(), cows.end());
  // 貪欲
  long long res = 0;
  for (int i = 0; i < n; i++) {
    dsum -= cows[i].d;
    res += dsum * cows[i].t;
  }

  cout << res << endl;
}

/*
考察
牛iは1分間に花をd[i]だけ破壊する。
ある牛jが移動するあいだ、2*t[j]*d[i]の花が破壊される。
和をとると2*t[j]*sigma{j以外}(d[i])
すべての牛を移動させるのにかかる時間は固定である。
2*sigma(t[i]).
d[i]の大きい順に連れて行くか？
  t d
a 100 100
b 1 50
この例なら、
a -> b 100 * 50 = 5000
b -> a 1 * 100 = 100
なので b -> a のほうが被害が小さい。
t[i]の小さい順ならどうだろうか？
早く連れて行ける牛から順に移動を済ませようという作戦である。
  t d
a 10 10
b  9 1
b -> a だと 90
a -> b だと 10
これが反例になる。
a * b が小さい順ならどうだろうか？
ある牛jが移動するあいだ、破壊される花の量は
2*t[j]*sigma(d[i]) - 2*t[j]*d[i]
1 * (100 + 50 - 50)
100 * (100 + 50 - 50)
t[j] * S - t[j] * d[j]
この値が小さい順かな。
  t d
a 1 1
b 10 10
a -> 10
b -> 10
----
  t d
a t[i] d[i]
b t[j] d[j]
a -> b
f_a = t[i] * (S + d[j]) + t[j] * S
b -> a
f_b = t[j] * (S + d[i]) + t[i] * S
f_a - f_b = t[i] * d[j] - t[j] * d[i]
この値が正ならa->bのほうが破壊量が大きいのでb->aを選ぶべき
*/
