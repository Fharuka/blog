/*
*POJ:3685: Matrix
[http://poj.org/problem?id=3685:title]
**問題概要
N * N の行列があり、i 行 j 列の要素が、 i * i + 100000 * i + j * j - 100000 * j + i * j で与えられる。この行列の小さい方から M 番目の要素を求める。
1 <= N <= 50000
**解法
行列の要素を全列挙してソートするやり方だと時間が足りない。
C(x): M 番目の要素は x 以上である
という判定を行って、 C(x) を満たす最大の x を二分探索で求めれば、それが答え。C(x) の判定方法を考える。C(x) は言い換えると、
「 x より小さい要素の個数が M 未満である」
ということだ。これは O(N log N) で判定可能だろうか。
要素の値を計算する関数を
>||
f(i, j) = i * i + 100000 * i + j * j - 100000 * j + i * j
||<
とする。
 f(i, j) は j を固定すると i に関して単調増加であある。
ということは、x よりも小さい要素の個数を数えるには、j に関してループを回しながら、 i に関して二分探索を行えば O(N log N) で判定可能である。

補足
int と long long が一つの式に出てくる計算は要注意。

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
const long long INF = 10000000000;
long long N;
long long M;

// i 行 j 列の要素の値
long long f(long long i, long long j) {
  return (long long)i * (i + 100000) + j * (i + j - 100000);
}

// ------ j 列目において x より小さい最大の要素が何行目なのかを二分探索
long long bi_search_i(long long j, long long x) {
    long long lb = 0, ub = 50010;

    while (ub - lb > 1) {
      long long mid = (lb + ub) / 2;
      if ( f(mid, j) < x) lb = mid;
      else ub = mid;
    }

    return lb;
}

//------- 条件 C(x) を満たす最大の x を求める二分探索
// 条件を満たすかどうかの関数
bool C(long long x) {
  long long cnt = 0;
  // 実装する
  for (long long j = 1; j <= N; j++) {
    cnt += min(N, bi_search_i(j, x));
  }
  // cout << x << " " << cnt << endl;
  return cnt < M;
}

// C(x) を満たす最大の x の二分探索
long long bi_search() {
  long long lb = -INF, ub = INF;

  while (ub - lb > 1) {
    long long mid = (lb + ub) / 2;
    if (C(mid)) lb = mid;
    else ub = mid;
  }

  return lb;
}


int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif

  int t;
  cin >> t;
  long long res;
  while (t--) {
    cin >> N >> M;

    res = bi_search();

    cout << res << endl;
  }
}
