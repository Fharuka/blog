/*

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

int main() {
  // 入力
  int n, c, v, b;
  long long res = 0;
  vector< pair<int, int> > vb;
  cin >> n >> c;
  for (int i = 0; i < n; i++) {
    cin >> v >> b;
    // 硬貨1枚で金額c以上になるものは先に支払う
    if (c <= v) {
      res += b;
    } else {
      vb.push_back(make_pair(v, b));
    }
  }
  sort(vb.begin(), vb.end());

  // 計算
  // lot: 1回の支払いで使うそれぞれの硬貨の枚数
  int m = vb.size();
  vector<int> lot(m);
  while (1) {
    int current = c;
    // 金額の高い硬貨から合計金額cを超えないように埋めていく
    for (int i = m -1; i >= 0; i--) {
      lot[i] = min(current / vb[i].first, vb[i].second);
      current -= lot[i] * vb[i].first;
      vb[i].second -= lot[i];
    }
    // 不足金額があり、かつ支払い可能であるなら、残っている硬貨のうち最も金額の小さい硬貨1枚で支払うことができる
    if (current > 0) {
      for (int i = 0; i < m; i++) {
        if (vb[i].second > 0) {
          vb[i].second--;
          lot[i]++;
          current -= vb[i].first;
          break;
        }
      }
    }
    // まだ支払い金額が残っているなら支払い不可能
    if (current > 0) break;
    res++;
    // lotの硬貨の組み合わせで支払える回数だけ支払う
    int num = INF;
    for (int i = 0; i < m; i++) {
      if (lot[i] > 0)
        num = min(vb[i].second / lot[i], num);
    }
    res += num;
    for (int i = 0; i < m; i++) {
      vb[i].second -= num * lot[i];
    }
  }

  // 出力
  cout << res << endl;
}
