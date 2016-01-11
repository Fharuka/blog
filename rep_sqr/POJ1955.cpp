/*
*POJ1995:
[http://poj.org/problem?id=1995:title]
*問題概要
与えられた整数の組を使ってべき乗の和の剰余を求める問題。
*解法
繰り返し二乗法でがんばる。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

//------- 大きな数の (a * b) % m -----------
long long modMult(long long a, long long b, long long m) {
  long long res = 0;
  long long exp = a % m;
  while (b) {
    if (b & 1) {
      res += exp;
      if (res > m) res -= m;
    }
    exp <<= 1;
    if (exp > m) exp -= m;
    b >>= 1;
  }
  return res;
}

//-------- べき剰余 (a ^ b) % m --------------------
long long powMod(long long a, long long b, long long m) {
  long long res = 1;
  long long exp = a % m;
  while (b) {
    if (b & 1) res = modMult(res, exp, m);
    exp = modMult(exp, exp, m);
    b >>= 1;
  }
  return res;
}

int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif

  // 入力
  int z;
  cin >> z;
  while (z--) {
    long long m;
    int h;
    cin >> m >> h;
    vector<long long> a(h);
    vector<long long> b(h);
    for (int i = 0; i < h; i++) {
      cin >> a[i] >> b[i];
    }
    // 計算
    long long sum = 0;
    for (int i = 0; i < h; i++) {
      sum += powMod(a[i], b[i], m);
      sum %= m;
    }
    cout << sum << endl;
  }
}
