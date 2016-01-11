/*
**POJ3126: Prime Path
[http://poj.org/problem?id=3126:title]
**問題概要
[http://wikiwiki.jp/pku/?3126%20Prime%20Path:title]
**解法
4桁の素数の表を作るのはエラトステネスのふるいでよい。
最短パスを見つけるためには幅優先探索で。
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int N = 10000;
typedef pair<int, int> P;

// ---- n ** m -----
int pow(int n, int m) {
  int res = 1;
  for (int i = 0; i < m; i++)
    res *= n;
  return res;
}

int main() {
  // エラトステネスのふるいで素数の表を作る
  bool isPrime[N];
  for (int i = 0; i < N; i++) {
    isPrime[i] = true;
  }
  isPrime[0] = false; isPrime[1] = false;
  for (int i = 0; i < N; i++) {
    if (isPrime[i]) {
      for (int j = i * 2; j < N; j += i) {
        isPrime[j] = false;
      }
    }
  }

  // 入力
  bool visited[N]; // すでに訪れた素数
  int n, p, q;
  cin >> n;
  while (n--) {
    // visited の初期化
    for (int i = 0; i < N; i++) {
      visited[i] = false;
    }
    cin >> p >> q;
    // 幅優先探索
    // pair (素数, 距離)
    queue<P> que;
    que.push(P(p, 0));
    visited[p] = true;
    int res_d = -1;
    while(!que.empty()) {
      P x = que.front();
      que.pop();
      int _p = x.first;
      int d = x.second;
      if (_p == q) {
        res_d = d;
        break;
      }
      int a, b, c, np;
      // p の一桁を違う数に置換した数を作る
      for (int i = 0; i < 4; i++) {
        a = pow(10, i);
        b = (_p / a) % 10;
        c = _p - b * a;
        for (int j = 0; j < 10; j++) {
          np = c + a * j;
          if (np >= 1000 && np != p && isPrime[np] && !visited[np]) {
            visited[np] = true;
            que.push(P(np, d + 1));
          }
        }
      }
    }
    // 出力
    if (res_d >= 0) {
      cout << res_d << endl;
    } else {
      cout << "Impossible" << endl;
    }
  }
}
