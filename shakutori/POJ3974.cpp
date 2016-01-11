/*


これは
manachar アルゴリズムという文字列に関する有名なものらしいぞ。
「manachar アルゴリズム」で検索すると出てくる。

*POJ: Palindrome
[http://poj.org/problem?id=3974:title]
**問題概要
文字列が与えらえるので、連続した文字を取り出して回文になっている部分文字列の最大文字数を求める。
**解法
文字列 s の i 番目を s[i] を表す。
左端が s[i] になっている最長の回文を見つけたとして、その右端が s[j] であるとしよう。
左端が s[i + 1] になっている最長の回文の左端はどうなっているだろうか？
それぞれの文字の個数が偶数である、という必要条件があるな。
a b a b c b a b
a bcdedcb a abcdedcb
a
aa
bab
cbabc

a が中心になる回文で最大のものを探す
c*b*a*b*c
隣の * を中心とした回文はあるか？
c*a*a*a*c
cbabc d
d を中心とした回文があるとすれば
cbabc d cbabc
って感じなる
次に調べるべきは
cbabc d cbabc e
*c*a*a*a*c* i = 5 len = 5
*c*a*a*c*   i = 4 len = 4
#aaaaaaaaa$

これだとダメだ

*a* i = 1
*a*a* i = 2
>|cpp|
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int MAX_N = 1000000;
int n; // 文字列の長さ
char s[MAX_N];
char str[MAX_N * 2];

int solve() {
  int res = 0;
  int c = 0; // c: 中心の位置
  while (c < n) {
    int i = 0;
    while (str[c - i] == str[c + i]) i++;
    res = max(res, i - 1 + (i - 1) % 2);
    c = max(c + 1, c + i - 2);
  }
  return res;
}



int main() {
  #ifndef ONLINE_JUDGE
  ifstream cin("../test.txt");
  #endif

  int num = 1;
  while (true) {
    scanf("%s", s);
    if (s[0] == 'E') break;
    // 中心のある回文だけを考えるために1文字ごとに'*'を挿入する
    memset(str, '*', sizeof(str));
    n = strlen(s);
    for (int i = 0; i < n; i++) {
      str[i * 2 + 1] = s[i];
    }
    // 両端の記号は変えておく
    str[0] = '#';
    str[2 * n] = '$';
    n = 2 * n + 1;

    // for (int i = 0; i < n; i++)
    //   cout << str[i];
    // cout << endl;

    int res = solve();
    cout << "Case " << num++ << ": " << res << endl;
  }
}
