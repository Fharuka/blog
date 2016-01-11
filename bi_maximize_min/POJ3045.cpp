#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int INF = 1010000000;
vector<pair<int, int> > cow;
int N;
int sum_w;

//------- 条件 C(x) を満たす最小の x を求める二分探索
// 条件を満たすかどうかの関数
bool C(int x) {
  priority_queue<int> que;
  int sum = sum_w;
  int w, s;
  for (int i = 0; i < N; i++) {
    s = cow[i].first;
    w = cow[i].second;
    while (sum > s + x) {
      if (que.empty()) return false;
      sum -= que.top();
      que.pop();
    }
    que.push(w);
  }
  return true;
}

// 二分探索
int bi_search() {
  int lb = -INF, ub = INF;

  while (ub - lb > 1) {
    int mid = (lb + ub) / 2;
    if (C(mid)) ub = mid;
    else lb = mid;
  }

  return ub;
}


int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif
  // 入力
  cin >> N;
  cow = vector<pair<int, int> >(N);
  sum_w = 0;
  int w, s;
  for (int i = 0; i < N; i++) {
    cin >> w >> s;
    cow[i] = make_pair(s + w, w);
    sum_w += w;
  }
  sort(cow.begin(), cow.end());
  reverse(cow.begin(), cow.end());

  int res = bi_search();

  cout << res << endl;
}
