/*
*POJ3292: Semi-prime H-numbers
[http://poj.org/problem?id=3292:title]
**問題概要
H-数を 4 * n + 1 で表せる正の整数とする。つまり、H-数とは 1, 5, 9, 13, ... である。
H-数は乗法について閉じている(2つの H-数の積はまた H-数になる)ので、ふつうの整数と同じように1や素数や合成数を定義できる。
・1 はそのまま 1 とする。
・H-数 h が "H-素数"であるとは、H-数の積に分解すると 1 * h の形にしかならないことをいう。ただし 1 は H-素数ではない。
・H-数 h が"H-合成数"であるとは、h を H-素数の積で表せることをいう。
さて、さらに H-擬素数というものを定義する。
・H-数 h が"H-擬素数"であろとは、ちょうど2つの H-素数の積で表せることをいう。
たとえば、 25 = 5 * 5 は H-擬素数であるが、 125 = 5 * 5 * 5 は H-擬素数でない。
与えられた H-数 h に対して、h 以下の H-擬素数の個数を求めるプログラムを書く。
**解法
変わった問題だが、ふつうにエラトステネスのふるいが通用する。
1000001 以下の素数を記録しておき、h 以下の擬素数の個数も先に計算しておく。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int N = 250001;

// m = 4 * i + 1 から i を求める
int to_i(int m) {
  return (m - 1) / 4;
}

int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif
  // エラトステネスのふるい
  bool isPrime[N]; // isPrime[i] = true は 4 * i + 1 が H-素数ということ
  vector<int> prime; // i 番目の H-素数
  for (int i = 0; i < N; i++)
      isPrime[i] = true;
  isPrime[0] = false;
  int m;
  for (int i = 0; i < N; i++) {
    if (isPrime[i]) {
      m = 4 * i + 1;
      prime.push_back(m);
      for (int j = 5; to_i(m * j) < N; j += 4) {
        isPrime[to_i(m * j)] = false;
      }
    }
  }

  int n = prime.size(); // 1000001以下の H-素数の個数
  // 4 * i + 1 が擬素数かどうか
  bool is_semi_prime[N];
  for (int i = 0; i < N; i++)
    is_semi_prime[i] = false;
  long long k;
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      k = (long long)prime[i] * prime[j];
      if (k <= 1000001 && k >= 0) {
        is_semi_prime[to_i(k)] = true;
      } else {
        break;
      }
    }
  }

  // 擬素数を数えておく
  int cnt_semi_primes[N];
  cnt_semi_primes[0] = 0;
  for (int i = 1; i < N; i++) {
    cnt_semi_primes[i] = cnt_semi_primes[i-1];
    if (is_semi_prime[i]) cnt_semi_primes[i]++;
  }

  // 入力と出力
  while (true) {
    int h;
    cin >> h;
    if (h == 0) break;
    cout << h << " " << cnt_semi_primes[to_i(h)] << endl;
  }
}
