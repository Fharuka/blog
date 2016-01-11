/*
*POJ:1930 Dead Fraction
[http://poj.org/problem?id=1930:title]
**問題概要
与えられた循環小数を既約分数に直す。ただし、どこから巡回しているかはわからない。既約分数に直したときに、分母がもっとも小さくなる分数を出力する。
**解法
約分なので、分母と分子を最大公約数で割ればよい。

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

// a, b の最大公約数
int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

int main() {
  ifstream cin("../test.txt");
  while (true) {
    // 入力
    char c[30];
    cin >> c;
    string s(c);
    if (s.length() == 1) break;
    // 数字部分を抜き出す
    int loc = s.find("...", 0);
    string digits = s.substr(2, loc - 2);
    int d = digits.length();
    int n = atoi(digits.c_str());
    // 循環する箇所についてループ
    int res_num = INF;
    int res_den = INF;
    for (int i = 1; i <= d; i++) {
      // 分数を作る
      int m = n / pow(10.0, i);
      int num = n - m;
      int den = (10 * pow(10.0, i - 1) - 1) * 10 * pow(10.0, d - i - 1);
      // 約分する
      int g = gcd(num, den);
      num /= g;
      den /= g;
      // 分母が小さければ結果を更新
      if (den < res_den) {
        res_den = den;
        res_num = num;
      }
    }
    // 出力
    cout << res_num << "/" << res_den << endl;
  }
}
