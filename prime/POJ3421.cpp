/*
*POJ3421: X-factor chains
**問題概要
[http://poj.org/problem?id=3421:title]
正の整数 X に対して長さ m の X-factor chain を次のような数列と定義する。
1 = X0, X1, X2, …, Xm = X
数列は次の性質を満たす。
Xi < Xi+1 かつ Xi は Xi+1 を割り切る。
X-factor chain の最大の長さと、そのような長さの chain がいくつあるかを求める。
x <= 2 ^ 20
**解法
X-factor chain は、1から始めて少しずつ素数をかけて X にすれば、最も長いものが作れる。
よって、最大の長さは、X を素因数分解したときの素数の個数に等しい。
また、長さが最大となる chain の個数は、素数をかける順番に依存するので、同じものを含む順列で計算する。
必要な素数は 2 ^ 10 以下なので、エラトステネスのふるいが速い。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int N = 1024;

// n!
long long factorial(int n) {
  long long res = 1;
  while (n > 1) {
    res *= n--;
  }
  return res;
}

int main() {
  ifstream cin("../test.txt");
  // エラトステネスのふるい
  bool isPrime[N];
  vector<int> prime; // i番目の素数
  for (int i = 0; i < N; i++)
    isPrime[i] = true;
  for (int i = 2; i < N; i++) {
    if (isPrime[i]) {
      prime.push_back(i);
      for (int j = 2 * i; j < N; j += i) {
        isPrime[j] = false;
      }
    }
  }
  int M = prime.size();

  int n;
  while (cin >> n) {
    // n を素因数分解する
    vector<int> factors(M);
    fill(factors.begin(), factors.end(), 0);
    int cnt_len = 0;
    for (int i = 0; i < M; i++) {
      while (n % prime[i] == 0) {
        n /= prime[i];
        factors[i]++;
        cnt_len++;
      }
      if (n == 1) break;
    }
    // 残った n が素数の場合
    if (n > 1) {
      cnt_len++;
    }
    // 最長 chain の個数を数える
    long long cnt_chains = factorial(cnt_len);
    for (int i = 0; i < M; i++) {
      if (factors[i] > 0) {
        cnt_chains /= factorial(factors[i]);
      }
    }
    // 出力
    cout << cnt_len << " " << cnt_chains << endl;
  }
}
