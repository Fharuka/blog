/*
*POJ3579: Median
[http://poj.org/problem?id=3579:title]
**問題概要
N 個の数 X[1], X[2], ..., X[N] の各数の差 |X[i] - X[j]| ( NC2 通りある)の中央値を求める。
3 <= N <= 100,000
X[i] <= 1,000,000,000
**解法
O(m) : 中央値が m 以上である
O(m) の判定があまり時間をかけずにできるなら（具体的には O(N log N) 以下の時間でできるなら）、中央値の検索に二分探索が有効に使える。つまり、O(m) を満たす最小の m が中央値である。
X[i] をソートしておく。A = NC2 とする。
発想としては、項の差が m 以下となるものを数えて、それが中央値の位置( (A - 1) / 2 )以下なら、中央値は m 以上であると判断できる。そこで、各 X[i] に対して、|X[i] - X[j]| <= m ( 0 <= j < i) となる j の個数 cnt[i] を数える。cnt[i] の和が (A - 1) /2 以下なら、中央値は m 以上であると言える。cnt[i] の数え方は O(N) で計算できる。
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
const int INF = 1000000000;
const int MAX_N = 100000;
int N;
int A;
int X[MAX_N];

//------- 条件 C(x) を満たす最大の x を求める二分探索
// 条件を満たすかどうかの関数
bool C(int m) {
  int cnt = 0;
  int l = 0;
  for (int i = 1; i < N; i++) {
    while (X[i] - X[l] > m) l++;
    cnt += i - l;
  }
  return cnt <= (A - 1) / 2;
}
// 二分探索
int bi_search() {
  int lb = 0, ub = INF;

  while (ub - lb > 1) {
    int mid = (lb + ub) / 2;
    if (C(mid)) lb = mid;
    else ub = mid;
  }

  return ub;
}


int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif

  while (cin >> N) {
    for (int i = 0; i < N; i++) {
      cin >> X[i];
    }
    sort(X, X + N);
    A = N * (N - 1) / 2;

    int res = bi_search();

    cout << res << endl;
  }
}
