#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

// N より小さいの素数を生成する(エラトステネスのふるい)
const int N = 20010;
int p;
vector<int> prime;
void make_prime() {
  bool isPrime[N];
  for (int i = 0; i < N; i++)
    isPrime[i] = true;
  isPrime[0] = false; isPrime[1] = false;
  for (int i = 1; i < N; i++) {
    if (isPrime[i]) {
      for (int j = 2 * i; j < N; j += i)
        isPrime[j] = false;
    }
  }

  for (int i = 1; i < N; i++) {
    if (isPrime[i])
      prime.push_back(i);
  }
}

// しゃくとり法
int count_prime_seq(int n) {
  int cnt = 0;
  int sum = 0, s = 0, t = 0; // [s, t)
  while (true) {
    while (t < p && sum < n) {
      sum += prime[t++];
    }
    if (prime[t-1] > n) break;
    if (sum == n) cnt++;
    sum -= prime[s++];
  }
  return cnt;
}


int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif

  // 素数生成
  make_prime();
  p = prime.size();

  while (true) {
    int n;
    cin >> n;
    if (!n) break;

    int res = count_prime_seq(n);

    cout << res << endl;
  }
}
