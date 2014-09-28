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
using pnode = shared_ptr<node>;
const int MAX = 2000;

int m[MAX][MAX];

struct node {
  bool visited;
  int index;
  vector<pnode> adjusted;
  pnode parent;
  int component;
};


int n;
vector<pnode> g;

int get_component(int i) {
  if (g[i]->component == i) return i;
  g[i]->component = get_component(g[i]->component);
  return g[i]->component;
}

void join_components(int i, int j) {
  i = get_component(i);
  j = get_component(j);
  g[i]->component = j;
}

bool process_row(int r) {
  vector<ii> s;
  int i;
  auto x = g[r];
  for (i = r + 1; i < n; ++i) s.emplace_back(m[r][i], i);
  sort(s.begin(), s.end());
  for (auto e : s) {
    bool ok = false;
    for (auto a : x->adjusted) {
      // cout << e.first << "==" << m[r][a->index] + m[a->index][e.second] << endl;
      if (e.first == m[r][a->index] + m[a->index][e.second]) {
        ok = true;
        break;
      }
    }
    if (ok) continue;
    if (get_component(x->index) == get_component(e.second)) return false;
    x->adjusted.emplace_back(g[e.second]);
    g[e.second]->adjusted.emplace_back(x);
    join_components(x->index, e.second);
  }
  return true;
}

int main() {
  int i, j;
  while (cin >> n) {
    g.resize(n);
    for (i = 0; i < n; ++i) {
      g[i] = make_shared<node>();
      g[i]->index = i;
      g[i]->component = i;
      for (j = 0; j < n; ++j) {
        cin >> m[i][j];
      }
    }
    bool ok = true;
    for (i = 0; i < n && ok; ++i) {
      if (m[i][i] != 0) ok = false;
      for (j = i + 1; j < n && ok; ++j) {
        if (m[i][j] != m[j][i] || m[i][j] == 0) ok = false;
      }
    }

    for (i = 0; i < n && ok; ++i) {
      ok = process_row(i);
    }

    if (ok) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
