#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
int n, k;
vector<int> a, b;
vector<double> v;
//------- 条件 C(x) を満たす最大の x を求める二分探索
// 条件を満たすかどうかの関数
bool C(double x) {
  for (int i = 0; i < n; i++) {
    v[i] = (double) 100 * a[i] - x * b[i];
  }

  sort(v.begin(), v.end());

  double sum = 0;
  for (int i = k; i < n; i++) {
    sum += v[i];
  }

  return sum >= 0;
}

// 二分探索
double bi_search() {
  double lb = 0, ub = 101;

  while (ub - lb > 0.001) {
    double mid = (lb + ub) / 2;
    if (C(mid)) lb = mid;
    else ub = mid;
  }

  return lb;
}

int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif
  while (true) {
    // 入力
    cin >> n >> k;
    if (!(n | k)) break;
    a = vector<int>(n);
    b = vector<int>(n);
    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = 0; i < n; i++)
      cin >> b[i];
    // 計算
    v = vector<double>(n);
    double res = bi_search();
    // 出力
    cout << floor(res + 0.5) << endl;
  }
}
