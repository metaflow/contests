#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

vector<set<l>> rows, cols;
vvb visited;
string answer;

void travel(l a, l b, char c) {
  l n = abs(a - b);
  for (l i = 0; i < n; i++) answer += c;
}

void dfs(l x0, l y0) {
  visited[x0][y0] = true;
  if (not rows[x0].count(y0)) answer += '1';
  rows[x0].erase(y0);
  cols[y0].erase(x0);
  // up
  if (not cols[y0].empty()) {
    for (l x = x0 - 1; x >= *(cols[y0].begin()); x--) {
      if (visited[x][y0]) break;
      if (rows[x].empty()) continue;
      travel(x0, x, 'U'); dfs(x, y0); travel(x0, x, 'D');
      break;
    }
  }
  // down
  if (not cols[y0].empty()) {
    for (l x = x0 + 1; x <= *(cols[y0].rbegin()); x++) {
      if (visited[x][y0]) break;
      if (rows[x].empty()) continue;
      travel(x0, x, 'D'); dfs(x, y0); travel(x0, x, 'U');
      break;
    }
  }
  // left
  if (not rows[x0].empty()) {
    for (l y = y0 - 1; y >= *(rows[x0].begin()); y--) {
      if (visited[x0][y]) break;
      if (cols[y].empty()) continue;
      travel(y0, y, 'L'); dfs(x0, y); travel(y0, y, 'R');
      break;
    }
  }
  // right
  if (not rows[x0].empty()) {
    for (l y = y0 + 1; y <= *(rows[x0].rbegin()); y++) {
      if (visited[x0][y]) break;
      if (cols[y].empty()) continue;
      travel(y0, y, 'R'); dfs(x0, y); travel(y0, y, 'L');
      break;
    }
  }
  // turn off
  answer += '2';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, x0, y0;
  while (cin >> n >> x0 >> y0) {
    x0--; y0--;
    answer = "";
    rows.clear(); cols.clear(); visited.clear();
    rows.resize(n); cols.resize(n); visited.resize(n, vb(n));
    for (l i = 0; i < n; i++) {
      for (l j = 0; j < n; j++) {
        l t; cin >> t;
        if (t == 0) continue;
        rows[i].emplace(j);
        cols[j].emplace(i);
      }
    }
    dfs(x0, y0);
    bool ok = true;
    for (auto& r : rows) ok = ok and r.empty();
    if (ok) {
      cout << "YES\n" << answer << '\n';
    } else {
      cout << "NO\n";
    }
  }
}
