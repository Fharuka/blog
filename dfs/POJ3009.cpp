/*
  問題
  惑星MM-21では、今年のオリンプックが終わってからカーリングが有名になった。けれども、ルールは私たちの星のルールとちょっと違っている。正方形のメッシュがマークされている氷のボードの上で試合が行われる。石はひとつだけ使う。ゲームの目的は、石をスタートからゴールまで、最小の移動回数で移動させることである。図1にゲームボードの例を示す。いくつかのマスにはブロックが置いてある。スタートとゴールのマスが一つずつあり、それらにはブロックが置かれていない。（スタートとゴールは異なるマスである。）一度石が動き始めると、ブロックに当たるまでまっすぐに進む。石をゴールにまで持っていくために、石をブロックに当てて止めてから、また投げなければならない。

  石の動き方は次のルールに従う。
  ・最初、石はスタートのマスにある。
  ・石の移動はx方向かy方向のみする。斜めの移動はできない。
  ・石は止まっているときに投げて動かすことができる。ブロックにすぐにぶつかる方向以外なら、どの方向にも投げられる。（図2(a)）
  ・一度石を投げると、以下のいずれかが起きるまで、石は同じ方向に移動し続ける。
    ・石がブロックにぶつかる（図2(b),(c)）。
      石はぶつかったブロックの隣のマスに止まる。
      ぶつかったブロックは消滅する。
    ・石がボードの外に出る。
      ゲームは失敗に終わる。
    ・石がゴールのマスに達する。
      石はゴールで止まり、ゲームは成功で終わる。
  ・一度のゲームの中で石を投げる回数は10回を超えてはならない。10回投げてもゴールに入らなければ、ゲームは失敗に終わる。

  このルールのもとで、スタートからゴールに達することが可能かどうか、また可能なら最小何回の移動が必要なのかを知りたい。

  図1の初期配置のとき、4回移動させれば、石をスタートからゴールに持っていくことができる。道筋を図3(a)に示した。石がゴールに達したとき、ボードの形は図3(b)のようになっていることに注意すること。
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_W = 20;
const int MAX_CNT = 10;
int w,h,sx,sy,gx,gy;
int board[MAX_W][MAX_W];
int four_direction[4][2] = {
    {1,0}, {-1,0}, {0,1}, {0,-1}
};


// ボードの外に出ているかどうか
bool isOutOfBoard(int x, int y) {
  return x < 0 || x >= w || y < 0 || y >= h;
}

//指定した方向の隣接ブロックを壊す
void breakBlock(int x, int y, int dx, int dy) {
  if (!isOutOfBoard(x + dx, y + dy) && board[y][x] != 3)
    board[y + dy][x + dx] = 0;
}

// 指定した方向の隣接ブロックを置き直す
void restoreBlock(int x, int y, int dx, int dy) {
  if (!isOutOfBoard(x + dx, y + dy) && board[y][x] != 3)
    board[y + dy][x + dx] = 1;
}


// 指定した方向に移動する。ブロックにぶつかるか外に出るまで
pair<int,int> moveTo(int x, int y, int dx, int dy) {
  int nx = x;
  int ny = y;
  while (!isOutOfBoard(nx, ny) &&
          (isOutOfBoard(nx + dx, ny + dy) || board[ny + dy][nx + dx] != 1) &&
          board[ny][nx] != 3) {
    nx += dx;
    ny += dy;
  }
  return pair<int,int>(nx, ny);
}

// 現在位置x,y
int dfs(int x, int y, int cnt) {
  // 現在位置がゴールだったら
  if (x == gx && y == gy)
    return cnt;
  // 10回投げ終わったら
  if (cnt == 10)
    return -1;

  int res = 100;
  pair<int, int> nxny;
  int nx, ny, dx, dy;
  // 4方向に移動させ、ブロックも壊す
  for (int i = 0; i < 4; i++) {
    dx = four_direction[i][0];
    dy = four_direction[i][1];
    if (isOutOfBoard(x + dx, y + dy) || board[y + dy][x + dx] == 1)
      continue;
    nxny = moveTo(x, y, dx, dy);
    nx = nxny.first;
    ny = nxny.second;
    if (!isOutOfBoard(nx, ny)) {
      breakBlock(nx, ny, dx, dy);
      int _res = dfs(nx, ny, cnt + 1);
      if (_res > 0)
        res = min(res, _res);
      restoreBlock(nx, ny, dx, dy);
    }
  }

  return (res == 100) ? -1 : res;
}



int main() {
//  ifstream ifs( "test2.txt" );
  while(true) {
    // 入力
    cin >> w >> h;
    if (!(w | h))
      break;
    // ボードを0で埋める
    for (int i = 0; i < MAX_W; i++) {
      for (int j = 0; j < MAX_W; j++) {
        board[i][j] = 0;
      }
    }
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        cin >> board[i][j];
        if (board[i][j] == 2) {
          sx = j;
          sy = i;
        } else if (board[i][j] == 3) {
          gx = j;
          gy = i;
        }
      }
    }

    // 深さ優先探索
    int res = dfs(sx, sy, 0);

    // 出力
    cout << res << endl;
  }
  return 0;
}
