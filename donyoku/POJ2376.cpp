/*
http://poj.org/problem?id=2376
ジョンはN(1 <= N <= 25000)頭の牛のうち何頭かを使って、小屋の周りを掃除させることにした。
つねに1頭は掃除の仕事をしているようにしたいと思い、
1日をT(1 <= T <= 1000000)個のシフトに分けた。
それぞれの牛は1日のうちある決まった期間にしか使えない。掃除の仕事のために選ばれた牛は、その期間全体に渡って働き続ける。
あなたの仕事は、ジョンが牛にシフトを割り当てるのを手伝うことだ。
(1)それぞれのシフトは少なくとも1頭の牛が割り当てられている。
(2)掃除をする牛はできるだけ少ないようにしたい。
それぞれのシフトに牛を割り当てるのが不可能なら-1を出力せよ。

牛の選び方は次の通り
(1) 最初の1頭は時間1から始まり終了時間が最も遅いものを選ぶ。
(2) i+1頭目の牛は、開始時間がi頭目の牛の終了時間以下の牛のうち、終了時間が最も遅い牛を選ぶ。
(3) 選んだ牛の終了時間がTと等しくなったら終了する
*/
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main() {
  // 入力
  int n, t;
  scanf("%d%d", &n, &t);
  // 各牛の開始時間と終了時間
  vector< pair<int, int> > cows(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &cows[i].first, &cows[i].second);
  }

  // 牛の開始時間が小さい順、終了時間が小さい順にソート
  sort(cows.begin(), cows.end());

  // 計算
  int i = 0;
  int cur_end_time;
  int cnt = 1;
  // 最初の1頭は開始時間が1から始まり終了時間が最も遅いものを選ぶ
  while (cows[i].first == 1 && i < n) {
    i++;
  }
  if (i == 0) {
    cout << -1 << endl;
    return 0;
  }
  cur_end_time = cows[i - 1].second;
  // i+1頭目の牛は開始時間がi頭目の牛の終了時間+1以下の牛のうち、終了時間が最も遅い牛を選ぶ。
  while (cur_end_time < t && i < n) {

    int next_end_time = cur_end_time;

    while (cows[i].first <= cur_end_time + 1 && i < n) {
      if (next_end_time < cows[i].second)
        next_end_time = cows[i].second;
      i++;
    }

    // next_end_timeが更新されていなければ、被覆は不可能
    if (cur_end_time == next_end_time) {
      cout<< -1 << endl;
      return 0;
    }
    cur_end_time = next_end_time;
    cnt++;
  }

  // 出力
  cout << ((cur_end_time == t) ? cnt : -1) << endl;
}
