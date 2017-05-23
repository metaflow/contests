#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
const bool enable_log = true;
#else
const bool enable_log = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

void apply(vll& events, l row, l column, l dr, l dc,
           vvl& tt, unordered_map<l, l>& time_pos, l h, l w) {
  set<l> s;
  l p = 0;
  while (row >= 0 and row < h and column >= 0 and column < w and p < events.size()) {
    l x = (dr != 0) ? row : column;
    while (p < events.size() and events[p].first == x) {
      l t = events[p].second;
      if (time_pos[t] == x) {
        s.emplace(t);
      } else {
        s.erase(t);
      }
      p++;
    }
    if (not s.empty()) {
      l t = *(s.crbegin());
      tt[row][column] = max(tt[row][column], t + abs(time_pos[t] - x));
    }
    row += dr;
    column += dc;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // solution
  l h, w, n;
  while (cin >> h >> w >> n) {
    vector<string> ss(h);
    F(i, 0, h) cin >> ss[i];
    vector<vector<ll>> up(w), down(w), right(h), left(h);
    unordered_map<l,l> time_pos;
    vvl tt(h, vl(w, -1));
    l row = h - 1, column = 0;
    tt[row][column] = 1;
    l t = 2;
    F(i, 0, n) {
      string op; l x; cin >> op >> x;
      switch (op[0]) {
      case 'u':
        up[column].emplace_back(make_pair(row - 1, t));
        time_pos[t] = row - 1;
        row -= x;
        up[column].emplace_back(make_pair(row - 1, t));
        break;
      case 'd':
        down[column].emplace_back(make_pair(row + 1, t));
        time_pos[t] = row + 1;
        row += x;
        down[column].emplace_back(make_pair(row + 1, t));
        break;
      case 'l':
        left[row].emplace_back(make_pair(column - 1, t));
        time_pos[t] = column - 1;
        column -= x;
        left[row].emplace_back(make_pair(column - 1, t));
        break;
      case 'r':
        right[row].emplace_back(make_pair(column + 1, t));
        time_pos[t] = column + 1;
        column += x;
        right[row].emplace_back(make_pair(column + 1, t));
        break;
      }
      t += x;
    }
    F(i, 0, w) {
      sort(all(up[i]), greater<ll>());
      apply(up[i], h - 1, i, -1, 0, tt, time_pos, h, w);
    }
    F(i, 0, w) {
      sort(all(down[i]));
      apply(down[i], 0, i, +1, 0, tt, time_pos, h, w);
    }
    F(i, 0, h) {
      sort(all(left[i]), greater<ll>());
      apply(left[i], i, w - 1, 0, -1, tt, time_pos, h, w);
    }
    F(i, 0, h) {
      sort(all(right[i]));
      apply(right[i], i, 0, 0, +1, tt, time_pos, h, w);
    }
    l from = 0;
    l to = t - 1;
    bool ok = true;
    F(r, 0, h) F(c, 0, w) {
      if (ss[r][c] == '.') {
        if (tt[r][c] == -1) continue;
        to = min(to, tt[r][c] - 1);
      } else {
        if (tt[r][c] == -1) ok = false;
        from = max(from, tt[r][c]);
      }
    }
    ok = ok and (from <= to);
    if (not ok) {
      cout << "-1 -1" << lf;
    } else {
      cout << from << ' ' << to << lf;
    }
  }
}
