/*
ストライピーと呼ばれるアメーバのような生物が群生している。
ストライピーは2匹が衝突すると合体する。
2匹のストライピーの重さをm1, m2とすると、合体したストライピーの重さは2*sqrt(m1*m2)である。
ストライピーの群れが合体を繰り返した時に合計の重さの下限を求めよ。
n <= 100
w <= 10000
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <set>
using namespace std;

int main() {
  // 入力
  int n;
  cin >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    cin >> w[i];
  }
  sort(w.begin(), w.end());
  // 計算
  // 重さの大きい順に合体させる。
  double res = *w.rbegin();
  for (int i = w.size() - 2; i >= 0; i--) {
    res = 2 * sqrt(res * w[i]);
  }
  // 出力
  printf("%.3f\n", res);
}
