/*
問題
0から9までのいくつかの数字が与えられ、数字を2つのグループに分けて2つの整数を作る。2つの整数の差の絶対値の最小値を求めよ。
*/
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;
const int INF = 1000000000;

int main() {
  // 入力
  int n;
  cin >> n;
  cin.ignore();
  while (n--) {
    int a[10];
    int res = INF;
    string str;
    getline(cin, str);
    stringstream s(str);
    int b, size = 0;
    while (s >> b) {
      a[size++] = b;
    }
    // 計算
    if (size == 2) {
      res = abs(a[0] - a[1]);
    } else {
      int x, y, half;
      half = size / 2;
      // 順列を全列挙して半分のところで分けて2つの整数を作る
      do {
        if (a[0] == 0 || a[half] == 0) continue;
        x = 0;
        y = 0;
        for (int i = 0; i < half; i++) {
          x *= 10;
          x += a[i];
        }
        for (int i = half; i < size; i++) {
          y *= 10;
          y += a[i];
        }
        res = min(res, abs(x - y));
      } while (next_permutation(a, a + size));
    }
    // 出力
    cout << res << endl;
  }
}
