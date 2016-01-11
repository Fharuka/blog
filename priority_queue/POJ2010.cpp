/*
[http://poj.org/problem?id=2010:title]
**問題概要
[http://wikiwiki.jp/pku/?2010%20Moo%20University%20-%20Financial%20Aid:title]
**解法
N=2*m+1とする。
ある整数iが、N個の数の中央値であるとは、N個の数をソートしたときにiがm+1番目に来ることである。つまり、iを除くと、i以下の数がm個、i以上の数がm個ある。「i以下の数」「i以上の数」はm個あるこどだけが必要十分で、じっさいにどんな数が来るかは関係ない。
そこで、次のように動的計画法のように考える。
牛たちを成績の低い順にソートしておく。
sum[i] = (i番目の牛を中央値としたときのN頭の最小コスト)
i番目の牛を中央値とする牛の選び方は、牛iを選んだ上で、1..(i-1)番目の牛からm頭選び（m頭とも牛iの成績以下である）、(i+1)..C番目の牛からm頭選べば（m頭とも牛iの成績以上である）よい。この選び方の中におけるaidの和の最小値がsum[i]の値である。
sum[i]の求め方にプライオリティキューを使う。プライオリティキューはaidの大きな順に取り出せるものとする。lessを「1..(i-1)番目の牛から最小コストとなるよう選んだm頭」を格納するためのプライオリティキューとし、moreを「(i+1)..C番目の牛から最小コストとなるよう選んだm頭」を格納するためのプライオリティキューとする。sum[i-1]の計算で、lessを「1..(i-2)番目の牛から最小コストとなるよう選んだm頭」を格納していれば、次のlessの計算は容易である。sum[i]では、lessに牛iをプッシュして、一番aidの大きな一頭をポップすればよい。つまり、sum[i-1]でlessを計算してあればsum[i]でlessが計算できる。同様にして、逆向きにすれば、sum[i+1]でmoreを計算してあれば、sum[i]でmoreが計算できる。
こうしてsum[i]をそれぞれ計算してから、F以下の最大のiが答えになる。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <set>
#include <utility>
#include <algorithm>
using namespace std;
int N, F, C; // 教室（奇数）、志願者、基金
struct Cow {
  int score, aid;
};

// 比較関数を定義(multiset用)
struct Asc_score{
public:
  bool operator()( const Cow& one, const Cow& another ) {
    if (one.score == another.score) {
      return one.aid < another.aid;
    } else {
      return one.score < another.score;
    }
  }
};

vector<int> cal_sum(vector<Cow> cows) {
  // 中央値以下の牛たちのaid
  priority_queue<int> less;
  // 合計コスト
  vector<int> sum(C);
  int m = N / 2;
  sum[m] = 0;
  for (int i = 0; i < m; i++) {
    less.push(cows[i].aid);
    sum[m] += cows[i].aid;
  }
  // lessを更新しながらsum[i]を計算
  for (int i = m + 1; i < C - m; i++) {
    if (cows[i - 1].aid < less.top()) {
      less.push(cows[i - 1].aid);
      sum[i] = sum[i-1] - less.top() + cows[i - 1].aid;
      less.pop();
    } else {
      sum[i] = sum[i-1];
    }
  }
  return sum;
}

int main() {
  // ifstream cin("../test.txt");
  // 入力
  cin >> N >> C >> F;
  // 成績の低い順
  multiset<Cow, Asc_score> cows_m;
  int s,a,i;
  for (i = 0; i < C; i++) {
    scanf("%d%d", &s, &a);
    Cow cow = {s, a};
    cows_m.insert(cow);
  }
  vector<Cow> cows(cows_m.begin(), cows_m.end());

  vector<int> sum_less = cal_sum(cows);
  reverse(cows.begin(), cows.end());
  vector<int> sum_more = cal_sum(cows);

  // cowsの並びを戻す
  reverse(cows.begin(), cows.end());

  // sumがF以下の最大の中央値を計算
  int m = N / 2;
  int res = -1;
  for (i = m; i < C - m; i++) {
    if (sum_less[i] + sum_more[C - i - 1] + cows[i].aid <= F) res = cows[i].score;
  }

  cout << res << endl;
}
