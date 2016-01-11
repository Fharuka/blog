#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
int n, k;
vector<int> v, w;
vector<double> ave;
//------- 条件 C(x) を満たす最大の x を求める二分探索
// 条件を満たすかどうかの関数
bool C(double x) {
  for (int i = 0; i < n; i++) {
    ave[i] = (double)v[i] - x * w[i];
  }
  sort(ave.begin(), ave.end());
  reverse(ave.begin(), ave.end());

  double sum = 0;
  for (int i = 0; i < k; i++)
    sum += ave[i];

  return sum >= 0;
}

// 二分探索
double bi_search() {
  double lb = 0, ub = 100000000;

  while (ub - lb > 0.00001) {
    double mid = (lb + ub) / 2;
    if (C(mid)) lb = mid;
    else ub = mid;
  }

  return ub;
}

// 平均が x であるような k 個の宝石の選び方を出力
void out(double x) {
  vector<pair<double, int> > jw(n);
  for (int i = 0; i < n; i++) {
    jw[i] = make_pair((double)v[i] - x * w[i], i + 1);
  }
  sort(jw.begin(), jw.end());
  reverse(jw.begin(), jw.end());

  double sum = 0;
  for (int i = 0; i < k-1; i++)
    cout << jw[i].second << " ";
  cout << jw[k-1].second << endl;
}

int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif
  // 入力
  cin >> n >> k;
  v   = vector<int>(n);
  w   = vector<int>(n);
  ave = vector<double>(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i] >> w[i];
  }
  // 計算
  double a = bi_search();

  // 出力
  out(a);
}
