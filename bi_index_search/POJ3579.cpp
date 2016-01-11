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
