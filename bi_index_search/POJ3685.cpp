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
