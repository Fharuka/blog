/*
*POJ3641: Pseudoprime Numbers
[http://poj.org/problem?id=3641:title]
**問題
[http://wikiwiki.jp/pku/?3641%20Pseudoprime%20numbers:title]
**解法
まあ、繰り返し二乗法だ。「擬素数は素数でない」という定義らしいので、p が素数かどうかもチェックしておく。べき剰余とか素数判定の関数はスパゲッティソースからお借りした。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

//------- 大きな数の (a * b) % m -----------
long long modMult(long long a, long long b, long long m) {
  long long res = 0;
  long long exp = a % m;
  while (b) {
    if (b & 1) {
      res += exp;
      if (res > m) res -= m;
    }
    exp <<= 1;
    if (exp > m) exp -= m;
    b >>= 1;
  }
  return res;
}

//-------- べき剰余 (a ^ b) % m --------------------
long long powMod(long long a, long long b, long long m) {
  long long res = 1;
  long long exp = a % m;
  while (b) {
    if (b & 1) res = modMult(res, exp, m);
    exp = modMult(exp, exp, m);
    b >>= 1;
  }
  return res;
}

//-------- Miilar-Robin Test による素数判定 -----------
bool suspect(long long a, int s, long long d, long long n) {
  long long x = powMod(a, d, n);
  if (x == 1) return true;
  for (int r = 0; r < s; ++r) {
    if (x == n - 1) return true;
    x = modMult(x, x, n);
  }
  return false;
}
// {2,7,61,-1}                 is for n < 4759123141 (= 2^32)
// {2,3,5,7,11,13,17,19,23,-1} is for n < 10^16 (at least)
bool isPrime(long long n) {
  if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
  int test[] = {2,3,5,7,11,13,17,19,23,-1};
  long long d = n - 1, s = 0;
  while (d % 2 == 0) ++s, d /= 2;
  for (int i = 0; test[i] < n && test[i] != -1; ++i)
    if (!suspect(test[i], s, d, n)) return false;
  return true;
}


int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif

  long long p, a;
  while (true) {
    cin >> p >> a;
    if (!(p | a)) break;
    long long a_p = powMod(a, p, p);
    if (a_p == a && !isPrime(p)) {
      cout << "yes" << endl;
    } else {
      cout << "no" << endl;
    }
  }
}
