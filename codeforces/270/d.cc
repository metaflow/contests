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
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
struct node;
const int MAX = 2000;

int m[MAX][MAX];

struct node {
  int index;
  vector<int> adjusted;
  int component;
};


int n;
vector<node> g;

int get_component(int i) {
  if (g[i].component == i) return i;
  g[i].component = get_component(g[i].component);
  return g[i].component;
}

void join_components(int i, int j) {
  i = get_component(i);
  j = get_component(j);
  g[i].component = j;
}

bool process_row(int r) {
  vector<ii> s;
  int i;
  for (i = r + 1; i < n; ++i) s.emplace_back(m[r][i], i);
  sort(s.begin(), s.end());
  for (auto e : s) {
    bool ok = false;
    for (auto a : g[r].adjusted) {
      if (e.first == m[r][a] + m[a][e.second]) {
        ok = true;
        break;
      }
    }
    if (ok) continue;
    if (get_component(r) == get_component(e.second)) return false;
    g[r].adjusted.emplace_back(e.second);
    g[e.second].adjusted.emplace_back(r);
    join_components(r, e.second);
  }
  return true;
}

int main() {
  int i, j;
  while (cin >> n) {
    g.clear();
    g.resize(n);
    bool ok = true;
    for (i = 0; i < n; ++i) {
      g[i].index = i;
      g[i].component = i;
      for (j = 0; j < n; ++j) {
        scanf("%d", &m[i][j]);
        if (j < i && (m[i][j] != m[j][i] || m[i][j] == 0)) ok = false;
      }
      if (m[i][i] != 0) ok = false;
    }

    for (i = 0; i < n && ok; ++i) ok = process_row(i);

    if (ok) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
