// 幅優先探索であらかじめすべての状態の最小手数を計算する
// 8!=40320なので、余裕で計算できる
// 最終状態01234567からさかのぼって幅優先探索

#include <iostream>
#include <queue>
#include <map>
using namespace std;
typedef pair<int, int> P;
// 最終状態01234567からある状態にするまでの最小手数
map<string,int> d;

void bfs() {
  // 最終状態への手数は0
  string start = "01234567";
  d[start] = 0;
  // キューを作る
  queue<string> qu;
  qu.push(start);
  // キューが空になるまでループ
  while(qu.size()) {
    string a = qu.front();
    qu.pop();
    int i = a.find_first_of('0');
    string s[3];
    s[0] = a;
    s[1] = a;
    s[2] = a;
    // 上下の交換
    int j = (i + 4) % 8;
    s[0].replace(i,1,1,s[0].at(j));
    s[0].replace(j,1,1,'0');
    // 右との交換
    if (i % 4 != 3) {
      s[1].replace(i,1,1,s[1].at(i+1));
      s[1].replace(i+1,1,1,'0');
    }
    // 左との交換
    if (i % 4 != 0) {
      s[2].replace(i,1,1,s[2].at(i-1));
      s[2].replace(i-1,1,1,'0');
    }
    // まだ最終手数がわかっていない文字列をキューにぶっこむ
    for (int k = 0; k < 3; k++) {
      if (d.find(s[k]) == d.end()) {
        qu.push(s[k]);
        d[s[k]] = d[a] + 1;
      }
    }
  }
}

int main() {
  // 先に最小手数のリストを作る
  bfs();

  // 入力と出力
  int n;
  while (true) {
    string str;
    for (int i = 0; i < 8; i++) {
      if (!(cin >> n)) return  0;
      str += n + '0';
    }
    cout << d[str] << endl;
  }
}
