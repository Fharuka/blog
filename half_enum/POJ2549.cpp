/*
*POJ2549: SUmsets
[http://poj.org/problem?id=2549:title]
**問題概要
1000 個以下の整数の集合において、a + b + c = d となる最大の d を見つける。
**解法
a と b を全列挙。c と　d を全列挙。二つ合わせて半列挙。
>|cpp|
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
using namespace std;
const int INF = 1000000000;
int n;
int s[1000];

int solve() {
  vector<pair<int, int> > ab; // a+b, aとbのインデックス
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      ab.push_back(make_pair(s[i] + s[j], 1000 * i + j));
    }
  }

  vector<pair<int, int> > cd; // d-c, cとdのインデックス
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cd.push_back(make_pair(s[j] - s[i], 1000 * i + j));
    }
  }
  sort(cd.begin(), cd.end());

  int res_d = -INF;

  int m = ab.size();
  set<int> abcd; // ai, bi, ci, di の重複確認用
  for (int i = 0; i < m; i++) {
    // ab[i] の値に対して a + b = d - c となる dc[i] を2分探索
    vector<pair<int, int> >::iterator lb;
    lb = lower_bound(cd.begin(), cd.end(), make_pair(ab[i].first, 0) );
    while ((*lb).first == ab[i].first) {
      int ai = ab[i].second / 1000;
      int bi = ab[i].second % 1000;
      int ci = (*lb).second / 1000;
      int di = (*lb).second % 1000;
      abcd.clear();
      abcd.insert(ai); abcd.insert(bi); abcd.insert(ci); abcd.insert(di);
      if (abcd.size() == 4) { // a,b,c,d がすべて異なる
        res_d = max(res_d, s[di]);
      }
      lb++;
    }
  }
  return res_d;
}

int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif

  while (true) {
    cin >> n;
    if (!n) break;
    for (int i = 0; i < n; i++) {
      cin >> s[i];
    }
    if (n < 4) {
      cout << "no solution" << endl;
      continue;
    }
    // sort(s, s + n);
    int res = solve();

    if (res != -INF)
      cout << res << endl;
    else
      cout << "no solution" << endl;
  }
}
