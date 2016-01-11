#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int N = 5;
const int M = 6;
int a[N][M]; // ライトの初期状態
int flips[N][M]; // 作業用
int min_flips[N][M]; // 結果保持用
int min_cnt;

bool is_one(int i, int j) {
  int res = a[i][j] + flips[i][j];
  if (i-1 >= 0) res += flips[i-1][j];
  if (i+1 < N)  res += flips[i+1][j];
  if (j-1 >= 0) res += flips[i][j-1];
  if (j+1 < M)  res += flips[i][j+1];

  return res % 2 == 1;
}

void calc() {
  // 縦で計算していく
  for (int j = 1; j < M; j++) {
    for (int i = 0; i < N; i++) {
      if (is_one(i, j -1 )) {
        flips[i][j] = 1;
      }
    }
  }

  // すべて 0 になっているか確認
  bool all_zero = true;
  for (int i = 0; i < N; i++) {
    if (is_one(i, M - 1))
      all_zero = false;
  }

  if (all_zero) {
    // flips を数える
    int cnt = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        cnt += flips[i][j];
      }
    }

    if (cnt < min_cnt) {
      min_cnt = cnt;
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
          min_flips[i][j] = flips[i][j];
        }
      }
    }
  }
}

void solve(int k) { // k: 問題番号
  min_cnt = M * N + 1;

  // 左端の縦列を全通り試す
  for (int i = 0; i < 1 << N; i++) {
    // flips 初期化
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        flips[i][j] = 0;
      }
    }

    for (int j = 0; j < N; j++) {
        flips[j][0] = i >> j & 1;
    }

    calc();
  }

  cout << "PUZZLE #" << k << endl;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cout << min_flips[i][j];
      cout << (j == M - 1 ? "\n" : " ");
    }
  }
}

int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif

  int n;
  cin >> n;
  for (int k = 1; k <= n; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        cin >> a[i][j];
      }
    }

    solve(k);
  }
}
