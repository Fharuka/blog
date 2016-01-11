/*
*POJ
[http://poj.org/problem?id=:title]
**問題概要
次の制約によって N 個のランプを取り付ける。H[i] はランプ i の高さである。
H[1] = A
H[i] = (H[i-1] + H[i+1])/2 - 1, for all 0 < i < N
H[i] >= 0, for all 0 <= i <= N
このとき、B = H[N] の最小値を求める。
3 <= N <= 1000
10 <= A <= 1000
**解法
H[1] は与えられているので、H[2] が決まればあとは H[N] まで全部決まるし、途中で H[i] < 0 になれば H[2] の値が不適切だということもわかる。そこで、H[2] の最小値を二分探索で求めて、それから H[N] を計算すればいい。

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
int N;
double A;

// H[2] を引数として H[N] を返す
double f(double x) {
  int n = N - 2;
  double h1, h2, h3;
  h3 = A;
  h2 = x;
  while (n--) {
    h1 = 2 * h2 - h3 + 2;
    // 更新
    h3 = h2;
    h2 = h1;
  }
  return h1;
}

//------- 条件 C(x) を満たす最小の x を求める二分探索
// 条件を満たすかどうかの関数
bool C(double x) {
  int n = N - 2;
  double h1, h2, h3;
  h3 = A;
  h2 = x;
  while (n--) {
    h1 = 2 * h2 - h3 + 2;
    // 更新
    h3 = h2;
    h2 = h1;
    if (h1 < 0) return false;
  }
  return true;
}

// H[N] を最小にする H[2] を二分探索
double bi_search() {
  double lb = 0, ub = 1000;

  int c = 100;
  while (c--) {
    double mid = (lb + ub) / 2;
    if (C(mid)) ub = mid;
    else lb = mid;
  }

  return ub;
}


int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif

  cin >> N >> A;

  double h2 = bi_search(); // H[2]
  double B = f(h2);

  printf("%.2f\n", B);
}
