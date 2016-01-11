/*
6種類の箱がある。箱の縦横はそれぞれ1*1,2*2,3*3,4*4,5*5,6*6となっている。
箱を入れる容器は縦横が6*6で、容器に箱をつめていく。
入力としてそれぞれの箱の数が与えられるので、箱をすべて詰めるのに最小でいくつの容器が必要かを求める。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

int main() {
  int p[6];
  while (1) {
    // 入力
    cin >> p[0] >> p[1] >> p[2] >> p[3] >> p[4] >> p[5];
    if (!(p[0] | p[1] | p[2] | p[3] | p[4] | p[5])) break;
    int cnt = 0;

    // 計算
    // 6*6
    cnt += p[5];
    // 5*5
    cnt += p[4];
    p[0] = max(p[0] - 11 * p[4], 0);
    // 4*4
    cnt += p[3];
    int i = max(5 * p[3] - p[1], 0);
    p[1] = max(p[1] - 5 * p[3], 0);
    p[0] = max(p[0] - 4 * i, 0);
    // 3*3
    cnt += (p[2] + 3) / 4; // 4で割って切り上げ
    i = p[2] % 4;
    if (i != 0) {
      int n = 7 - 2 * i; // 5 3 1
      while (n > 0) {
        if (p[1] > 0) {
          p[1]--;
        } else {
          p[0] = max(p[0] - 4, 0);
        }
        n--;
      }
      p[0] = max(p[0] - (8 - i), 0);
    }
    // 2*2
    cnt += (p[1] + 8) / 9; // 9で割って切り上げ
    if (p[1] % 9 != 0)
      p[0] = max(p[0] - 4 * (9 - p[1] % 9), 0);
    // 1*1
    cnt += (p[0] + 35) / 36; // 36で割って切り上げ

    // 出力
    cout << cnt << endl;
  }
}
