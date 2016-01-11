#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int MAX = 302;
const int INF = 10000000;
typedef pair<int, int> P;
int h,w,n;
// 移動の4方向
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
// 各座標に隕石が落ちる時間を格納する
int field[MAX][MAX];
// 各座標に到着したときの時刻
int d[MAX][MAX];

// 幅優先探索
// 移動した先がすでに隕石が落ちていたら死亡させていく
int bfs() {
  // スタート地点は(0,0)
  queue<P> qu;
  qu.push(P(0, 0));
  d[0][0] = 0;
  // スタート地点に最初から隕石が落ちていたら終了
  if (field[0][0] == 0)
    return -1;

  // queueが空になるまでループ
  while (qu.size()) {
    // queueから1つ座標を取り出す
    P p = qu.front();
    int x = p.first;
    int y = p.second;
    qu.pop();
    // INFなら終了
    if (field[x][y] == INF) {
      return d[x][y];
    }
    // 4方向
    for (int j = 0; j < 4; j++) {
      int nx = x + dx[j];
      int ny = y + dy[j];
      // 移動可能判定など
      if (nx >= 0 && nx <= MAX && ny >= 0 && ny <= MAX &&
          d[x][y] + 1 < field[nx][ny] && d[nx][ny] == INF) {
        d[nx][ny] = d[x][y] + 1;
        qu.push(P(nx,ny));
      }
    }
  }
  // quが空になったら安全地帯に到達できない
  return -1;
}

int main() {
  // 入力
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      field[i][j] = INF;
      d[i][j] = INF;
    }
  }
  int m;
//  ifstream ifs( "test.txt" );
  cin >> m;
  int x, y, t;
  for (int i = 0; i < m; i++) {
    cin >> x >> y >> t;
    field[x][y] = min(t,field[x][y]);
    // 周囲にも隕石の影響がある
    for (int j = 0; j < 4; j++) {
      int nx = abs(x + dx[j]);
      int ny = abs(y + dy[j]);
      field[nx][ny] = min(t, field[nx][ny]);
    }
  }

  // 計算
  int res = bfs();

  // 出力
  cout << res << endl;
}
