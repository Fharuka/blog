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
