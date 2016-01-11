/*
*POJ2429: GCD & LCM Inverse
[http://poj.org/problem?id=2429:title]
**問題概要
ある2つの自然数 a, b の最大公約数 GCD と最小公倍数 LCM が与えられるので、もとの a と b を求める。
**解法
最大公約数が g である数の組は、a, b ともにgの倍数であり、かつ gcd(a / g, b / g) = 0 。
最小公倍数が l である数の組は、a, b ともに l の約数で、かつ lcm(l / a, l / b)

60 / 3 = 20
20 = 4 * 5

結局、TLE を越えられなかった。
Java だと通るのに、 C++ だと通らない悲しさ。
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

//------- a と b の最小公倍数 ------
int gcd(long long a, long long b) {
  long long tmp;
  while (b != 0) {
    a %= b;
    tmp = a;
    a = b;
    b = tmp;
  }
  return a;
}

int main() {
  // ifstream cin("../test.txt");
  long long g, l, a, b, i, m;
  while (cin >> g >> l) {
    m = l / g;
    if (isPrime(m)) {
      a = g;
      b = m * g;
    } else {
      for (i = sqrt((long double)m); i > 0; i--) {
        if (m % i == 0 && gcd(i, m / i) == 1) {
          a = i * g;
          b = m / i * g;
          break;
        }
      }
    }
    cout << a << " " << b << endl;
  }
}
