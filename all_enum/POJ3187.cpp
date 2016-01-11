/*
  1からNまでの数が1行目に並んでいる。
  2行目以降は隣り合う数の和が書かれている。
  N=4
  3 1 2 4
   4 3 6
    7 9
     16
  N=4と最終和(16)から最初の並びを決定したい。
*/
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main() {
  // 入力
  int n, sum;
  cin >> n >> sum;

  // 計算
  // 順列を全列挙して調べる
  vector<int> v(n);
  // iota(v.begin(), v.end(), 1);
  for (int i = 0; i < n; i++)
    v[i] = i + 1;
  int a[10];
  do {
    for (int i = 0; i < n; i++)
      a[i] = v[i];
    // 順列vに対して最終和を計算する
    for (int i = n; i > 1; i--) {
      for (int j = 0; j < i; j++) {
        a[j] += a[j+1];
      }
    }
    // a[0]が最終和. sumと等しければ結果を出力
    if (a[0] == sum) {
      cout << v[0];
      for (int i = 1; i < n; i++) {
        cout << " " <<v[i];
      }
      cout << endl;
      return 0;
    }
    // next_permutationの威力
  } while (next_permutation(v.begin(), v.end()));
}
