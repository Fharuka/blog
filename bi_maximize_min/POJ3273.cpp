/*
*POJ3273: Monthly Expense
[http://poj.org/problem?id=3273:title]
**問題概要
N 個の整数からなる数列が与えられる。これを M 個の区間に分ける。区間は1つ以上の連続する項からなる。区間にある項の和の最大値を最小化するように区間を定めよ。
1 <= N <= 100,000
**解法
区間にある項の和の最大値が x 以下となるような区間分けが可能かどうかは、 O(N) で判定できる。そのような条件を満たす最小の x を探索するには、二分探索で OK 。

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
vector<int> money;
int N, M;
//------- 条件 C(x) を満たす最小の x を求める二分探索
// 条件を満たすかどうかの関数
bool C(int x) {
  // 貪欲法で判定する
  // つまり、項の和がつねに x 以下となるように次々と項をとっていく
  int cnt_m = 0;
  int sum = 0;
  for (int i = 0; i < N; i++) {
    if (money[i] > x) {
      return false;
    }
    sum += money[i];
    if (sum > x) {
      sum = money[i];
      cnt_m++;
    }
  }
  return cnt_m < M;
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
  cin >> N >> M;
  money = vector<int>(N);
  for (int i = 0; i < N; i++) {
    cin >> money[i];
  }

  // 二分探索
  int res = bi_search();

  cout << res << endl;
}
