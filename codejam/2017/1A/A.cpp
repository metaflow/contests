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
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

const l MAX = 30;
l n, m;

void mark(l r, l c, l v, vector<vvl>& anti) {
  F(i, r, n) F(j, c, m) F(k, 0, MAX) {
    if (v == k) continue;
    anti[k][i + 1][j + 1]++;
  }
}

l sum(vvl& a, l x1, l y1, l x2, l y2) {
  if (x1 > x2) swap(x1, x2);
  if (y1 > y2) swap(y1, y2);
  return a[x2 + 1][y2 + 1] + a[x1][y1]
    -a[x2 + 1][y1] - a[x1][y2 + 1];
}

void fill(vvl& cake, l v, l x1, l y1, l x2, l y2, vector<vvl>& anti) {
  if (x1 > x2) swap(x1, x2);
  if (y1 > y2) swap(y1, y2);
  F(i, x1, x2 + 1) F(j, y1, y2 + 1) {
    if (cake[i][j]) {
      assert(cake[i][j] == v);
      continue;
    }
    cake[i][j] = v;
    mark(i, j, v, anti);
  }
}

void solve(vvl& cake) {
  vector<vvl> anti(MAX, vvl(n + 1, vl(m + 1)));
  vector<ll> c1(MAX), c2(MAX);
  vector<bool> present(MAX);
  F(i, 0, n) F(j, 0, m) {
    l x = cake[i][j];
    if (not x) continue;
    present[x] = true;
    c1[x] = make_pair(i, j);
    c2[x] = make_pair(i, j);
    mark(i, j, x, anti);
  }
  F(i, 0, n) F(j, 0, m) {
    if (cake[i][j]) continue;
    F(k, 0, MAX) {
      if (not present[k]) continue;
      if ((sum(anti[k], i, j, c1[k].first, c1[k].second) == 0) and
          (sum(anti[k], i, j, c2[k].first, c1[k].second) == 0) and
          (sum(anti[k], i, j, c1[k].first, c2[k].second) == 0) and
          (sum(anti[k], i, j, c2[k].first, c2[k].second) == 0)) {
        c1[k].first = min(c1[k].first, i);
        c1[k].second = min(c1[k].second, j);
        c2[k].first = max(c2[k].first, i);
        c2[k].second = max(c2[k].second, j);
        fill(cake, k, c1[k].first, c1[k].second, c2[k].first, c2[k].second, anti);
        break;
      }
    }
    if (cake[i][j] == 0) {
      LOG << i << ' ' << j << endl;
    }
    assert(cake[i][j]);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  F(tc, 1, tcc + 1) {
    cin >> n >> m;
    vvl cake(n, vl(m));
    F(i, 0, n) {
      string s; cin >> s;
      F(j, 0, m) {
        if (s[j] != '?') cake[i][j] = s[j] - 'A' + 1;
      }
    }
    solve(cake);
    cout << "Case #" << tc << ":\n";
    F(i, 0, n) {
      F(j, 0, m) cout << (char)(cake[i][j] + 'A' - 1);
      cout << lf;
    }
  }
}
