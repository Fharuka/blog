/*
*AOJ0005 GCD and LCM
**問題
[http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0005&lang=jp]
*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

int main() {
  ifstream cin("../test.txt");
  int a, b, g;
  long long l;
  while (cin >> a >> b) {
    g = gcd(a, b);
    l = a / g * b / g * g;
    cout << g << " " << l << endl;
  }
}
