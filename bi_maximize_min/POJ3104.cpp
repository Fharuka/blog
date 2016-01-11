/*
*POJ3104:
[http://poj.org/problem?id=3104:title]
**問題概要
洗濯物が n 個ある。それぞれの洗濯物には水分が a[i] 含まれている。自然乾燥だと、洗濯物は1分で1だけ水分が減る。乾燥機を使うと1分で k だけ水分が減る。乾燥機は一度に1つの洗濯物にしか使えない。洗濯物がすべて乾くまでの時間を最小化せよ。
**解法
x 分以下で洗濯物を乾かせるかどうかの判定は O(n) でできる。乾燥機が x 回使えるので、それぞれの洗濯物が　x　分以下で乾くように乾燥機を使ったとして、乾燥機の使用回数が x を超えないかどうかをチェックすればよい。あとは x の最小値は二分探索で。
あるいは、別の解法で、単純な貪欲法でも解けそう。「毎分、水分が最も多く残っている洗濯物を乾燥機に放り込む」というルールで乾かせばいいと思う。
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
