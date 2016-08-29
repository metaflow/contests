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

struct node {
  int t, m, in;
  vector<pnode> adjusted;
};

int main() {
  int tcc, r; string s;
  cin >> tcc;
  getline(cin, s);
  getline(cin, s);
  for (int tc = 0; tc < tcc; tc++) {
    if (tc) cout << endl;
    vector<pnode> g(26);
    for (auto &u : g) {
      u = make_shared<node>();
      u->m = 0;
      u->in = 0;
    }
    while (getline(cin,s)) {
      if (s == "") break;
      stringstream ss(s);
      char a; string adjusted; int t;
      ss >> a >> t >> adjusted;
      auto &u = g[a - 'A'];
      u->t = u->m = t;
      for (auto c : adjusted) {
        u->adjusted.push_back(g[c - 'A']);
        g[c - 'A']->in++;
      }
    }
    r = 0;
    queue<pnode> q;
    for (auto u : g) if (u->in == 0) q.push(u);
    while (!q.empty()) {
      auto u = q.front(); q.pop();
      r = max(r, u->m);
      for (auto v : u->adjusted) {
        v->m = max(v->m, u->m + v->t);
        v->in--;
        if (v->in == 0) q.push(v);
      }
    }
    cout << r << endl;
  }
}
