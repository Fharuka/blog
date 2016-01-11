#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int INF = 1000000000;
const int N = 100000;
int n, k;
int a[N];
//------- 条件 C(x) を満たす最小の x を求める二分探索
// 条件を満たすかどうかの関数
bool C(int x) {
  // 実装する
  long long cnt_use = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] > x) {
      cnt_use += (a[i] - x) / (k - 1);
      cnt_use += ((a[i] - x) % (k - 1) != 0);
    }
  }
  return cnt_use <= x;
}

// 二分探索
int bi_search() {
  int lb = 0, ub = INF;

  while (ub - lb > 1) {
    int mid = (lb + ub) / 2;
    if (C(mid)) ub = mid;
    else lb = mid;
  }

  return ub;
}


int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif

  // 入力
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  cin >> k;

  int res;
  if (k > 1) {
    // 二分探索
    res = bi_search();
  } else {
    // k == 1 なら乾燥機がないのと同じ
    res = 0;
    for (int i = 0; i < n; i++) {
      res = max(res, a[i]);
    }
  }

  // 出力
  cout << res << endl;
}
