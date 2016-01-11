/*
[http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2170:title]
**問題概要
ノードがN個の木が与えられる。ノードには1からNの番号がつけられ、根は1である。木に対して二つの操作を考える。
M v: ノードvにマークする。
Q v: ノードvに最も近いマークされた先祖の番号を返す。
Q個の操作が与えられるので、操作Qで返される番号の総和を出力せよ。

**解法
どこがUnion-Find木を使うんだろうと思った。
ちょっと考えると、これは木を「分離」していく問題だ。でも、Union-Find木は木を「合併」するのに長けているデータ構造だ。どうやって利用すればいいのだろうか。と、ここまで考えて解答を見た。
http://acm-icpc.aitea.net/index.php?2009%2FPractice%2F%E5%A4%8F%E5%90%88%E5%AE%BF%2F%E8%AC%9B%E8%A9%95
なるほど。
クエリを後ろから処理するらしい。マークを外していく。そうするとUnion-Find木の要領で合併ができるな。
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

//------- Union-Find木 ---------
vector<int> par; // 親
// 初期化
void init(int n) {
  par = vector<int>(n);
  par[0] = 0;
}

// 木の根を求める
int find(int x) {
  if (par[x] == x) {
    return x;
  } else {
    return par[x] = find(par[x]);
  }
}

// xとyの属する集合を併合
void unite(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y) return;
  par[x] = y;
}

// xとyが同じ集合に属するか否か
bool same(int x, int y) {
  return find(x) == find(y);
}
//-------------------

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  // ifstream cin ("2170_input.txt");
  int N, Q;
  while (1) {
    cin >> N >> Q;
    if (!(N | Q)) break;
    init(N);
    int a, i;
    for (i = 1; i < N; i++) {
      cin >> a;
      par[i] = a - 1;
    }
    vector<pair<char, int> > query(Q);
    char q;
    for (i = 0; i < Q; i++) {
      cin >> q >> a;
      query[i] = make_pair(q, a);
    }

    // 先にマークする。つまり木を分離する。親となるノードを覚えておく(ori_par)。
    // 同じノードに2回以上マークしている場合も考慮する(ori_par_cnt)。
    map<int, int> ori_par;
    map<int, int> ori_par_cnt;
    for (i = 0; i < Q; i++) {
      if (query[i].first == 'M') {
        a = query[i].second - 1;
        if (!ori_par_cnt.count(a)) {
          ori_par[a] = par[a];
          ori_par_cnt[a] = 1;
          par[a] = a;
        } else {
          ori_par_cnt[a]++;
        }
      }
    }

    // クエリを後ろから処理する
    long long sum = 0;
    reverse(query.begin(), query.end());
    for (i = 0; i < Q; i++) {
      a = query[i].second - 1;
      if (query[i].first == 'Q') {
        sum += find(a) + 1;
      } else if (query[i].first == 'M') {
        if (ori_par_cnt[a] == 1) {
          unite(a, ori_par[a]);
        } else {
          ori_par_cnt[a]--;
        }
      }
    }

    // 出力
    cout << sum << endl;
  }
}
