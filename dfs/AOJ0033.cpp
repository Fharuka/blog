#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int a[10];
vector<int> b,c;

bool dfs(int i) {
  if (i == 10) {
    // 判定
    for (int j = 1; j < b.size(); j++) {
      if (b[j] < b[j-1])
        return false;
    }
    for (int j = 1; j < c.size(); j++) {
      if (c[j] < c[j-1])
        return false;
    }
    return true;
  }

  bool res = false;

  b.push_back(a[i]);
  res = res || dfs(i+1);
  b.pop_back();
  c.push_back(a[i]);
  res = res || dfs(i+1);
  c.pop_back();

  return res;
}

int main() {
  // ifstream ifs( "test.txt" );
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    // 入力
    for (int j = 0; j < 10; j++) {
      cin >> a[j];
    }
    b.clear();
    c.clear();
    // 計算
    bool res = dfs(0);
    // 出力
    cout << ((res) ? "YES" : "NO")<< endl;
  }
}
