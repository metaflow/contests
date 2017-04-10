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
#define ALL(x) begin(x), end(x)
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

bool bipartite_matching_connect(const int u, vvb& m, vl& to, vb& used) {
  for (size_t v = 0; v < to.size(); v++) {
    if (!m[u][v] || used[v]) continue;
    used[v] = true;
    if (to[v] == -1 || bipartite_matching_connect(to[v], m, to, used)) {
      to[v] = u;
      return true;
    }
  }
  return false;
}

// {A} => {B}, m[i][j] == A[i] -> B[j]
vl bipartite_matching(vvb& m) {
  if (m.empty()) return vl(0);
  vl to(m[0].size(), -1);
  int result = 0;
  for (size_t u = 0; u < m.size(); u++) {
    vb used(to.size());
    if (bipartite_matching_connect(u, m, to, used)) result++;
  }
  return to;
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  F(tc, 1, tcc + 1) {
    LOG << "tc " << tc << endl;
    l n, m;
    cin >> n >> m;
    vl rows(n), cols(n), d1(2*n - 1), d2(2*n - 1);
    vvl area(n, vl(n));
    l score = 0;
    set<ll> changes;
    F(i, 0, m) {
      l r, c;
      char a;
      cin >> a >> r >> c; r--; c--;
      l v;
      switch (a) {
      case 'x': v = 1; break;
      case '+': v = 2; break;
      case 'o': v = 3; break;
      default: assert(false);
      }
      area[r][c] = v;
      if (v % 2) {
        assert(rows[r] == 0);
        assert(cols[c] == 0);
        rows[r] = 1;
        cols[c] = 1;
        score++;
      }
      if (v > 1) {
        assert(d1[r + c] == 0);
        assert(d2[r - c + n - 1] == 0);
        d1[r + c] = 1;
        d2[r - c + n - 1] = 1;
        score++;
      }
    }
    // place 'x's
    F(r, 0, n) {
      if (rows[r]) continue;
      F(c, 0, n) {
        if (cols[c]) continue;
        assert(area[r][c] % 2 == 0);
        area[r][c] += 1;
        changes.emplace(r, c);
        rows[r] = 1;
        cols[c] = 1;
        score++;
        break;
      }
    }
    vvb match(d1.size(), vb(d2.size()));
    // place '+'s
    F(i, 0, d1.size()) {
      if (d1[i]) continue;
      F(j, 0, d2.size()) {
        if (d2[j]) continue;
        l r = i + j - n + 1;
        l c = i - j + n - 1;
        if (r < 0 or c < 0) continue;
        if ((r % 2) or (c % 2)) continue;
        r /= 2; c /= 2;
        if ((r >= n) or (c >= n)) continue;
        match[i][j] = true;
      }
    }
    vl is = bipartite_matching(match);
    F(j, 0, is.size()) {
      l i = is[j];
      if (i == -1) continue;
      l r = (i + j - n + 1) / 2;
      l c = (i - j + n - 1) / 2;
      if (area[r][c] >= 2) {
        LOG << r << ' ' << c << ' ' << area[r][c] << endl;
      }
      assert(area[r][c] < 2);
      area[r][c] += 2;
      changes.emplace(r, c);
      score++;
    }
    cout << "Case #" << tc << ": " << score << ' ' << changes.size() << '\n';
    for (auto c : changes) {
      switch (area[c.first][c.second]) {
      case 1: cout << 'x'; break;
      case 2: cout << '+'; break;
      case 3: cout << 'o'; break;
      default:
        LOG << area[c.first][c.second] << endl;
        assert(false); break;
      }
      cout << ' ' << (c.first + 1) << ' ' << (c.second + 1) << '\n';
    }
  }
}
