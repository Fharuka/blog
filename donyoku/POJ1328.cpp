/*
xy平面のy>0の領域にn(1 <= n <= 1000)個の島がある。
島の座標が与えられている。
中心がx軸上にある半径dの円をいくつか置いて島を被覆するには、
最小で何個の円を置けばよいかを求めよ。
円は中心がx軸上にあればどこにおいてもよい。
円で島を被覆できないときには-1を出力せよ。
解法
実質的には線分の被覆問題である。
貪欲法。島をx座標が小さい順にソートする。
左の島から被覆する。次のルールに従う。
まだ被覆されていない島のうちいちばん左の島をiとする。
島iから始めて順に島i+1, 島i+2...と連続した番号の島をまとめて被覆できる最大の円を取ようにする。
*/
//#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

int main() {
  // ifstream cin( "test.txt" );
  int c = 0;
  while (1) {
    // 入力
    c++;
    int n, d;
    cin >> n >> d;
    if (!(n | d)) break;
    int x, y;
    double dx;
    bool fail = false;
    vector< pair<double , double> >  lines(n);
    for (int i = 0; i < n; i++) {
      cin >> x >> y;
      if (y > d) {
        fail = true;
      } else {
        dx = sqrt((double)(d*d - y*y));
        lines[i] = make_pair(x - dx, x + dx);
      }
    }
    // 被覆できない島があるなら
    if (fail) {
      cout << "Case " << c << ": -1" << endl;
      continue;
    }
    // 線分の左端が小さい順、右端が小さい順にソート
    sort(lines.begin(), lines.end());
    // 計算
    double left = lines[0].first;
    double right = lines[0].second;
    int i = 0;
    int cnt = 1;
    // 線分がなくなるまでループ
    while (++i < n) {
      // 連続して被覆できなくなったら
      if (right < lines[i].first) {
        cnt++;
        left = lines[i].first;
        right = lines[i].second;
        continue;
      }
      // 左端と右端を更新
      left = max(left, lines[i].first);
      right = min(right, lines[i].second);
    }

    // 出力
    cout << "Case " << c << ": " <<cnt << endl;
  }
}
