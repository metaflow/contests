#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <queue>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

using vi = vector<int>;
using matrix = vector<vector<int>>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

matrix apply(matrix &a, matrix &b) {
  int i, j, k;
  matrix c(a.size());
  for (i = 0; i < (int)a.size(); i++) {
    c[i].resize(b[0].size());
    for (j = 0; j < (int)c[i].size(); j++) {
      c[i][j] = 0;
      for (k = 0; k < (int)b.size(); k++) c[i][j] += a[i][k] * b[k][j];
    }
  }
  return c;
}

void printm(matrix a) {
  for (auto r : a) {
    for (auto i : r) cout << i << " ";
    cout << endl;
  }
}

bool match(matrix &a, matrix &b) {
  int i, j;
  for (i = 0; i < (int)a.size(); i++)
  for (j = 0; j < (int)a[i].size(); j++)
    if (a[i][j] != b[i][j]) return false;
  return true;
}

int main() {
  int tcc, i, j, n, m;
  cin >> tcc;
  vector<matrix> t = {
    {{0, 0, 1},
    {0, 1, 0},
    {-1, 0, 0}},

    {{1, 0, 0},
    {0, 0, -1},
    {0, 1, 0}},

    {{0, 1, 0},
    {-1, 0, 0},
    {0, 0, 1}}};

  vector<matrix> o = {
      {{1}, {0}, {0}},
      {{0}, {0}, {1}},
      {{0}, {0}, {-1}},
      {{0}, {-1}, {0}},
      {{0}, {1}, {0}},
      {{-1}, {0}, {0}}
    };

  while (tcc--) {
    vector<string> names(6);
    for (i = 0; i < 6; i++) cin >> names[i];
    cin >> n;
    vector<matrix> p = o;
    vector<pair<char, int>> ops(n);
    for (i = 0; i < n; i++) cin >> ops[i].first >> ops[i].second;
    for (auto h = ops.crbegin(); h != ops.crend(); h++) {
      m = h->second % 4;
      while (m--) {
        for (auto &a : p) a = apply(t[h->first - 'X'], a);
      }
    }

    vector<string> solution;

    for (j = 0; j < (int)p.size(); j++) {
      if (j != 0) cout << " ";
      for (i = 0; i < (int)o.size(); i++) {
        if (!match(p[j], o[i])) continue;
        cout << names[i];
        break;
      }
    }
    cout << endl;
  }
}
