/*
[http://poj.org/problem?id=3614:title]
**問題概要
C頭の牛にL個の日焼け止めを塗る。日焼け止めiのSPF値はSPF[i]であり、cover[i]頭の牛にぬることができる。各牛はminSPF[i]以上maxSPF[i]以下のSPF値の日焼け止めを必要としている。最大で何頭の牛を日焼けから守れるか。
1 <= C <= 2,500
1 <= L <= 2,500
1 <= SPF[i] <= 2,500
1 <= minSPF[i] <= 2,500
1 <= maxSPF[i] <= 2,500

**解法
蟻本ではプライオリティキューの練習問題として出されていたが、プライオリティキュー使わなくても解ける普通の貪欲法の問題だった。いちおう、ソートの代わりに無理やり使ってみたけど。
日焼け止めはSPF値の高い順に取り出す。牛はminSPFの高い順にソートする。日焼け止めの塗り方は、minSPF <= SPF[i] <= maxSPFを満たす牛のうち、minSPFの高い牛から塗っていく。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

struct Cow {
  int minSPF, maxSPF;
  bool operator>(const Cow& another) const {
    if (minSPF == another.minSPF) {
      return maxSPF > another.maxSPF;
    } else {
      return minSPF > another.minSPF;
    }
  }
};

struct Lotion {
  int SPF, cover;
  bool operator<(const Lotion& another) const {
    return SPF < another.SPF;
  }
};

int main() {
  // ifstream cin("../test.txt");
  // 入力
  int C, L;
  cin >> C >> L;
  vector <Cow> cow(C);
  priority_queue <Lotion> lotion;
  int i, a, b;
  for (i = 0; i < C; i++) {
    cin >> a >> b;
    Cow d = {a, b};
    cow[i] = d;
  }
  sort(cow.begin(), cow.end(), greater<Cow>());
  i = L;
  while(i--) {
    cin >> a >> b;
    Lotion e = {a, b};
    lotion.push( e );
  }

  int res = 0;
  Cow w;
  vector<Cow>::iterator it;
  // 日焼け止めがなくなるまでループ
  while (lotion.size()) {
    Lotion l = lotion.top();
    lotion.pop();
    it = cow.begin();
    while (it != cow.end() && l.cover) {
      w = *it;
      if (w.minSPF <= l.SPF && l.SPF <= w.maxSPF) {
        res++;
        l.cover--;
        cow.erase(it);
      } else {
        it++;
      }
    }
  }

  // 出力
  cout << res << endl;
}
