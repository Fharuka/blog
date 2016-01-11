#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
int a[20];
int flips[20]; // 反転させた場所を記録


// i 番目が 1 かどうか
bool is_one(int i) {
  int res = a[i];
  res += flips[i];
  if (i - 1 >= 0)
    res += flips[i - 1];
  if (i + 1 < 20)
    res += flips[i + 1];
  return res % 2 == 1;
}

int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif

  for (int i = 0; i < 20; i++) {
    cin >> a[i];
  }


  int res = 20;
  // a[0] をひっくり返す場合とひっくり返さない場合を考える
  // flips[0] が決まればあとは自動的に他の flips[i] も決まる
  for (int j = 0; j < 2; j++) {
    int cnt = j;
    flips[0] = j;
    for (int i = 1; i < 20; i++)
      flips[i] = 0;

    for (int i = 1; i < 20; i++) {
      if (is_one(i - 1)) {
        flips[i] = 1;
        cnt++;
        // cout << " " << j << endl;
      }
    }
    // 不可能判定
    for (int i = 0; i < 20; i++)
      if (is_one(i)) continue;

    res = min(res, cnt);
  }


  cout << res << endl;
}
