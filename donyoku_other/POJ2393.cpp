#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  // 入力
  int n, s;
  cin >> n >> s;
  vector<int> c(n);
  vector<int> y(n);
  for (int i = 0; i < n; i++) {
    cin >> c[i] >> y[i];
  }

  // 計算
  int i = 0;
  // 現在の最小コスト
  int min_y = 10000;
  int cost;
  long long total = 0;
  // 先週までの最小コストの週を保管した場合と今週のコストを比較して、最小コストを更新する
  do {
    // 最小コストの更新
    min_y = min(c[i], min_y + s);

    total += y[i] * min_y;
  } while (++i < n);

  // 出力
  cout << total << endl;
}
