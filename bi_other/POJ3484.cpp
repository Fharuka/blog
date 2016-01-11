#include <cstdio>
#include <cstring>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
vector<long long> x, y, z;
char buf[1025];
int N = 0;

//------- 条件 C(x) を満たす最小の x を求める二分探索
const long long INF = 100000000000;
// C(x) : 奇数回出現する整数が m 以下に存在する
long long C(long long m) {
  long long cnt = 0; // すべての数の出現回数の総和
  for (int i = 0; i < N; i++) {
    long long mx = min(m, y[i]);
    // x, x + z, x + 2*z, ... x + k*z <= mx の個数は k + 1
    if (mx >= x[i])
      cnt += (mx - x[i]) / z[i] + 1;
  }

  return cnt;
}
// 二分探索
long long bi_search() {
  long long lb = 0, ub = INF;

  while (ub - lb > 1) {
    long long mid = (lb + ub) / 2;
    if (C(mid) % 2) ub = mid;
    else lb = mid;
  }

  return ub;
}

bool init(){
	int f = 0;
	N = 0;
  x.clear(); y.clear(); z.clear();
  long long _x, _y, _z;
	while((f = ((fgets(buf, 1025, stdin)!=NULL))) && strlen(buf) > 2){
		sscanf(buf, "%lld%lld%lld", &_x, &_y, &_z);
    x.push_back(_x);
    y.push_back(_y);
    z.push_back(_z);
    N++;
	}

	return f || N > 0;
}

void solve() {
  if (N == 0) return;
  if (C(INF) % 2 == 0) {
    cout << "no corruption" << endl;
  } else {
    long long res = bi_search();
    cout << res << " " << C(res) - C(res-1) << endl;
  }
}

int main() {
  while (init()) {
    solve();
  }
}
