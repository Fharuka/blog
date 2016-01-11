#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int INF = 1000000000;
int L, N, M;
vector<int> D;

//------- 条件 C(x) を満たす最大の x を求める二分探索
// 長さ x を最小距離とするような岩の配置は可能か
bool C(int x) {
  int pos = 0;
  int j = 0;
  int cnt = 0;
  while (j <= N) {
    if (D[j] - pos < x) {
      j++;
      cnt++;
    } else {
      pos = D[j];
      j++;
    }
  }
  return cnt <= M;
}

// 二分探索
int bi_search() {
  int lb = 0, ub = INF;

  while (ub - lb > 1) {
    int mid = (lb + ub) / 2;
    if (C(mid)) lb = mid;
    else ub = mid;
  }

  return lb;
}


int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif

  cin >> L >> N >> M;
  D = vector<int>(N + 1);
  for (int i = 0; i < N; i++) {
    cin >> D[i];
  }
  D[N] = L;
  sort(D.begin(), D.end());

  int res = bi_search();

  cout << res << endl;
}
