/*
*POJ: Subset
[http://poj.org/problem?id=3977:title]
**問題概要
N ( N <= 35) 個の数からなる集合において、空でない部分集合の和の絶対値が最小となるときの、最小値とその部分集合の要素数を求める。
**解法
集合を2つに分けてそれぞれの部分和を全列挙する。N / 2 <= 17 なので、全列挙は高々 2^17 = 131072 通り。これを M とすると、二つの集合の部分和同士の和で絶対値が 0 に近いものは2分探索すればいいので、計算時間は O(M log M) 。
絶対値が最小となるときの部分集合の要素数も求めないといけないので、pair でデータを扱った。そしたら first と second ばっかりの汚いコードになってしまい、可読性が最悪だ。
>|cpp|
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const long long INF = 100000000000000000;
int N;
long long a[35];
long long b[35];

long long _abs(long long m) {
  return m >= 0 ? m : -m;
}

void solve() {
  // 集合を2つに分割してそれぞれを全列挙。それから和を組み合わせる
  if (N == 1) {
    cout << _abs(a[0]) << " " << 1 << endl;
    return;
  }
  int n = N / 2;
  vector< pair<long long, int> > sum_a(1 << n);
  vector< pair<long long, int> > sum_b(1 << (N - n));

  for (int i = 0; i < 1 << n; i++) {
    sum_a[i] = make_pair(0,0);
    for (int j = 0; j < n; j++)
      if (i >> j & 1) {
        sum_a[i].first += a[j];
        sum_a[i].second++;
      }
  }

  for (int k = n; k < N; k++) b[k - n] = a[k];
  for (int i = 0; i < 1 << (N - n); i++) {
    sum_b[i] = make_pair(0, 0);
    for (int j = 0; j < N - n; j++)
      if (i >> j & 1) {
        sum_b[i].first += b[j];
        sum_b[i].second++;
      }
  }

  pair<long long, int> min_sum = make_pair(INF, 0);
  // sum_a からだけ or sum_b からだけ
  for (int i = 1; i < 1 << n; i++)
    // min_sum = min(min_sum, abs(sum_a[i].first));
    if (min_sum.first > _abs(sum_a[i].first)) min_sum = make_pair( _abs(sum_a[i].first), sum_a[i].second);
    else if (min_sum.first == _abs(sum_a[i].first)) min_sum.second = min(min_sum.second, sum_a[i].second);

  for (int i = 1; i < 1 << (N - n); i++)
    // min_sum = min(min_sum, abs(sum_b[i].first));
    if (min_sum.first > _abs(sum_b[i].first)) min_sum = make_pair( _abs(sum_b[i].first), sum_b[i].second);
    else if (min_sum.first == _abs(sum_b[i].first)) min_sum.second = min(min_sum.second, sum_b[i].second);

  // 空集合を削除
  sum_a.erase(sum_a.begin());
  sum_b.erase(sum_b.begin());

  sort(sum_b.begin(), sum_b.end());

  // sum_a の要素と sum_b の要素の和の絶対値の最小値を2分探索
  for (int i = 0; i < (1 << n) - 1; i++) {
    vector< pair<long long, int> >::iterator lb = lower_bound(sum_b.begin(), sum_b.end(), make_pair(-sum_a[i].first, 0));
    if (lb != sum_b.end()) {
      long long sm = _abs(sum_a[i].first + (*lb).first);
      if (min_sum.first > sm) min_sum = make_pair(sm, sum_a[i].second + (*lb).second);
      else if (min_sum.first == sm) min_sum.second = min(min_sum.second, sum_a[i].second + (*lb).second);
    }

    if (lb != sum_b.begin()) {
      long long sm = _abs(sum_a[i].first + (*(--lb)).first);
      if (min_sum.first > sm) min_sum = make_pair(sm, sum_a[i].second + (*lb).second);
      else if (min_sum.first == sm) min_sum.second = min(min_sum.second, sum_a[i].second + (*lb).second);
    }
  }
  cout << min_sum.first << " " << min_sum.second << endl;
}

int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif

  while (true) {
    cin >> N;
    if (!N) break;
    for (int i = 0; i < N; i++) {
      cin >> a[i];
    }
    solve();
  }
}
