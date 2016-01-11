/*
  問題文の翻訳はrubyのフォルダにあるよ
*/

#include <iostream>
using namespace std;

const int MAX_W = 20;
int w,h,cnt,sx,sy;
char tiles[MAX_W + 2][MAX_W + 2];

// 現在位置x,y
void dfs(int x, int y) {
  if (tiles[y][x] == '#') {
    return;
  }

  tiles[y][x] = '#';
  cnt++;

  dfs(x + 1, y);
  dfs(x - 1, y);
  dfs(x, y + 1);
  dfs(x, y - 1);
}

int main() {
  while(true) {
    // 入力
    cnt = 0;
    cin >> w >> h;
    if (w == 0) {
      break;
    }

    // 処理しやすくするためにタイルの周辺は'#'で埋める
    for (int i = 1; i <= h; i++) {
      tiles[i][0] = '#';
      tiles[i][w+1] = '#';
      for (int j = 1; j <= w; j++) {
        cin >> tiles[i][j];
        if (tiles[i][j] == '@') {
          sx = j;
          sy = i;
        }
      }
    }
    for (int i = 0; i <= w+1; i++) {
      tiles[0][i] = '#';
      tiles[h+1][i] = '#';
    }

    dfs(sx,sy);

    // 出力
    cout << cnt << "\n";
  }
}
