/*
*AOJ2200: Mr.Rito Post Office
[http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2200:title]
**解法
N <= 200 の全点対最短経路問題なので、基本はワーシャルフロイド法。しかし、海路がひと癖ある。海路を通って町iに来た場合、あとで再び海路を使うには町iからでなければならないという制約があるので、ちょっと考えなくてはいけない。

結論としては、ワーシャルフロイドと動的計画法を組み合わせることにする。

まず、任意の2つの町の最短距離を、陸路のみを使った場合と海路のみを使った場合でそれぞれ求めることにする。
つまり、次の二つを計算する。
>>|cpp|
dl[x][y] = (町xから町yに陸路のみを使って行く最短距離)
ds[x][y] = (町xから町yに海路のみを使って行く最短経路)
||<
これらはワーシャルフロイドで求められる。この時点では、船がどこに置いてあるかは気にしなくて良い。町xから町yに陸路のみでは行けない場合や、海路のみでは行けない場合もあるので、そのときには dl[x][y] = INF、 ds[x][y] = INF などとする。

次に、i番目の集荷が終わった時点での最短距離を求めたい。

ところが、船がどこに泊めてあるかによって最短距離は変わってくるので、dpを次のように定義する。

dp[i][j] = (i番目の集荷までの最短距離。ただしi番目の集荷が終わった時点で船がjに泊まっている)

集荷にあたって、町xから町yへの移動方法は2通りある。陸路と海路の両方を使う場合と、陸路のみを使う場合である。
町x -> 陸路で港町kへ -> 海路で港町jへ -> 陸路で町yへ
町x -> 陸路で町yへ
このことを考慮して漸化式を作ると、次の通り。
>|cpp|
s = z[i-1];
g = z[i];
dp[i][j] = min(
  dp[i-1][j] + dl[s][g],
  dp[i-1][k] + dl[s][k] + ds[k][j] + dl[j][g] の最小値 for k in 0..N
);
||<

あとは素直に実装すればよい。

*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int INF = 10000000;
const int MAX_N = 200;
const int MAX_R = 1000;
//struct edge {int };

int main() {
  // ifstream cin("../test.txt");
  while (true) {
    int N, M;
    cin >> N >> M;
    if (!(N | M)) break;
    // dl, dsの初期化
    int dl[MAX_N][MAX_N]; // 陸路の最短距離
    int ds[MAX_N][MAX_N]; // 海路の最短距離
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (i == j) {
          dl[i][i] = 0;
          ds[i][i] = 0;
        } else {
          dl[i][j] = INF;
          ds[i][j] = INF;
        }
      }
    }
    int x, y, t;
    char sl;
    while (M--) {
      cin >> x >> y >> t >> sl;
      x--; y--;
      if (sl == 'L') {
        dl[x][y] = t;
        dl[y][x] = t;
      } else if (sl == 'S') {
        ds[x][y] = t;
        ds[y][x] = t;
      }
    }
    // ワーシャルフロイド
    for (int k = 0; k < N; k++) {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          dl[i][j] = min(dl[i][j], dl[i][k] + dl[k][j]);
          ds[i][j] = min(ds[i][j], ds[i][k] + ds[k][j]);
        }
      }
    }
    // dp 初期化
    int dp[MAX_R][MAX_N];
    int z[MAX_R];
    int R;
    cin >> R;
    for (int i = 0; i < R; i++) {
      cin >> z[i];
      z[i]--;
    }
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < N; j++) {
        dp[i][j] = INF;
      }
    }
    dp[0][z[0]] = 0;
    for (int j = 0; j < N; j++) {
      dp[0][j] = ds[z[0]][j];
    }
    // dp 計算
    int s, g;
    for (int i = 1; i < R; i++) {
      for (int j = 0; j < N; j++) {
        s = z[i-1];
        g = z[i];
        // dp[i-1][k] + dl[s][k] + ds[k][j] + dl[j][g] の最小値
        int min_s = INF;
        for (int k = 0; k < N; k++) {
          if (INF > dp[i-1][k] + dl[s][k] + ds[k][j])
            min_s = min(min_s, dp[i-1][k] + dl[s][k] + ds[k][j]);
        }
        min_s += dl[j][g];
        dp[i][j] = min(dp[i-1][j] + dl[s][g], min_s);
      }
    }
    // 出力
    int ans = INF;
    for (int i = 0; i < N; i++) {
      ans = min(ans, dp[R-1][i]);
    }
    cout << ans << endl;
  }
}
