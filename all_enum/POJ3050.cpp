/*
  5*5のマス。縦横に5回移動して6桁の整数を作る。何通りの整数ができるか。
  Input
  1 1 1 1 1
  1 1 1 1 1
  1 1 1 1 1
  1 1 1 2 1
  1 1 1 1 1
  Output
  15

  111111, 111112, 111121, 111211, 111212, 112111, 112121, 121111, 121112, 121211, 121212, 211111, 211121, 212111, and 212121 can be constructed. No other values are possible.
*/
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
// 5*5の数を格納
int field[5][5];
// 結果となる6桁の数を格納
set<int> nums;
// 枝刈りのため
set<int> done;
// 4方向
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

// 枝刈りしながら深さ優先探索
void dfs(int x, int y, int n, int cnt) {
  // 5回投げたら
  if (cnt == 6) {
    // numsに要素が見つからなけれあば追加する
    if (nums.find(n) == nums.end()) {
      nums.insert(n);
      // cout << n << endl;
    }
    return;
  }

  // 枝刈り
  int a = 1000 * n + 100 * x + 10 * y + cnt;
  if (done.find(a) != done.end()) {
    return;
  }
  done.insert(a);

  // 4方向
  int nx, ny;
  for (int i = 0; i < 4; i ++) {
    nx = x + dx[i];
    ny = y + dy[i];
    // 外にはみ出ていなければ
    if (nx >= 0 && nx < 5 && ny >= 0 && ny < 5) {
      dfs(nx, ny, 10 * n + field[nx][ny], cnt + 1);
    }
  }
}

int main() {
  // 入力
  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 5; y++)
      cin >> field[x][y];
  }

  // 計算
  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 5; y++)
      dfs(x, y, 0, 0);
  }

  // 出力
  cout << nums.size() << endl;
}
