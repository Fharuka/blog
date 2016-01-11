/*
http://poj.org/problem?id=3190
A..B(1 <= A <= B <= 1000000)の時間帯にしかミルクを出さない牛がN頭(1 <= N <= 50000)いる。ひとつの搾乳ブースには一頭の牛しか一度に使えない。
・それぞれの牛がプライベートなミルク時間を持てるような搾乳ブースの最小数を求めたい
・牛はミルク時間のあいだずっと搾乳ブースを占領する

残っている牛の中で開始時間が最も早いものを選ぶ。
すでにあるブースの中で終了時間が最も早いものにその牛が入れば入れる。
その牛が入らなければ新しいブースを作る。
*/
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
using namespace std;

struct Cow {
  int id, ts, te, stl;
  // ふつうの比較<は終了時間teにより比較（逆）
  bool operator<(const Cow& another) const {
    return another.te < te;
  }
};
// 開始時間tsにより比較
bool comp1(Cow one, Cow another) {
  return one.ts < another.ts;
}
// idにより比較
bool comp2(Cow one, Cow another) {
  return one.id < another.id;
}

int main() {
  // 入力
  // ifstream cin( "test.txt" );
  int n, i, j;
  cin >> n;
  // cowsには各牛の搾乳の開始時間と終了時間を格納する
  vector< Cow > cows(n);
  for (i = 0; i < n; i++) {
    cows[i].id = i;
    cin >> cows[i].ts >> cows[i].te;
  }
  // 開始時間の早い順にソート
  sort(cows.begin(), cows.end(), comp1);
  // stallsには牛が終了時間の早い順に入る
  priority_queue<Cow> stalls;
  // 計算
  i = 0;
  j = 1;
  int tmp;
  cows[0].stl = j++;
  stalls.push(cows[0]);
  while (++i < n) {
    // すでに区画への配置が決まっている牛の中で終了時間が最も早いもの
    Cow c = stalls.top();
    // 残った牛のうち開始時間が最も早い牛が、牛cのいる区画に入れるなら
    if (cows[i].ts > c.te) {
      cows[i].stl = c.stl;
      stalls.pop();
      stalls.push(cows[i]);
    // 入れないなら新たに区画を作る
    } else {
      cows[i].stl = j++;
      stalls.push(cows[i]);
    }
  }

  // 出力
  cout << stalls.size() << endl;
  sort(cows.begin(), cows.end(), comp2);
  for(i = 0; i < n; i++)
    cout << cows[i].stl << endl;
}
