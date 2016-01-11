/*
*POJ2566: Bound Found
[http://poj.org/problem?id=2566:title]
**問題概要

**解法
https://gist.github.com/amoshyc/57f3f07eeceec85d287b
>|cpp|
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int INF = 2000000000;
const int MAX_N = 100001;
int N, K, T;
int a[MAX_N];
pair<int, int> S[MAX_N]; // a[0] から a[i] の累積和
int ans_sum = 0, ans_s = -1, ans_e = -1;

void solve() {
  int l = 0, r = 1;
  int min_diff = INF, sum = 0;

  while (r <= N) {
    sum = abs(S[r].first - S[l].first);
    if (abs(sum - T) < min_diff) {
      min_diff = abs(sum - T);
      ans_sum = sum;
      ans_s = min(S[l].second, S[r].second) + 1;
      ans_e = max(S[l].second, S[r].second);
    }
    if (sum < T || l == r - 1)
      r++;
    else
      l++;
  }
}

int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif

  while (cin >> N >> K) {
    if (!(N | K)) break;

    for (int i = 1; i <= N; i++)
      cin >> a[i];

    S[0] = make_pair(0, 0);
    for (int i = 1; i <= N; i++) {
        S[i].first = S[i-1].first + a[i];
        S[i].second = i;
    }
    sort(S, S + N + 1);

    while (K--) {
      cin >> T;
      solve();
      cout << ans_sum << " " << ans_s << " " << ans_e << endl;
    }
  }
}
