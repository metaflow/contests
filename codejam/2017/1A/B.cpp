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

// intervals are inclusive [a, b]
// e.g. [1, 2] + [2, 3] -> [1, 3]
// [1, 4] - [2, 3] -> [1, 1], [4, 4]
// and find([4, 7]) -> ([1, 4], [5, 6], [7, 11])
class MergedIntervals {
private:
  struct cmp {
    bool operator() (const ll& a, const ll& b) {
      return a.second < b.first;
    };
  };
  set<ll, cmp> m;
  friend ostream& operator << (ostream& s, const MergedIntervals& v) {
    for (auto i = v.m.cbegin(); i != v.m.cend(); i++) {
      s << "[" << i->first << ", " << i->second << "] ";
    }
    return s;
  }
public:

  void add(l a, l b) {
    auto p = m.equal_range(make_pair(a, b));
    for (auto i = p.first; i != p.second; i++) {
      a = min(a, i->first);
      b = max(b, i->second);
    }
    m.erase(p.first, p.second);
    m.emplace(make_pair(a, b));
  }
  void add(ll s) { add(s.first, s.second); }

  void remove(ll s) {
    auto p = m.equal_range(s);
    vll r;
    for (auto i = p.first; i != p.second; i++) r.emplace_back(*i);
    m.erase(p.first, p.second);
    for (auto i : r) {
      if (i.first < s.first) {
        m.emplace(make_pair(i.first, min(s.first, i.second) - 1));
      }
      if (i.second > s.second) {
        m.emplace(make_pair(max(s.first, i.first) + 1, i.second));
      }
    }
  }
  void remove(l a, l b) { remove(make_pair(a, b)); }

  // returns all intervals intersecting with [a,b]
  // may be outside of [a, b]
  vll find(l a, l b) {
    vll r;
    auto p = m.equal_range(make_pair(a, b));
    for (auto i = p.first; i != p.second; i++) r.emplace_back(*i);
    return r;
  }

  // returns intersections with interval
  vll intersect(ll s) {
    vll r;
    auto p = m.equal_range(s);
    for (auto i = p.first; i != p.second; i++) {
      r.emplace_back(max(s.first, i->first), min(s.second, i->second));
    }
    return r;
  }
  vll intersect(l a, l b) { return intersect(make_pair(a, b)); }

  void intersect(MergedIntervals& other) {
    MergedIntervals result;
    for (auto s : other.m) {
      for (auto i : intersect(s)) result.add(i);
    }
    swap(*this, result);
  }

  bool intersectsWith(ll s) {
    auto p = m.equal_range(s);
    return p.first != p.second;
  }
  bool intersectsWith(l a, l b) { return intersectsWith(make_pair(a, b)); }

  // all intervals, ordered
  vll intervals() {
    vll r;
    r.insert(r.begin(), m.cbegin(), m.cend());
    return r;
  }
};

ll f(l p, l s) {
  return make_pair((100 * p + s * 110 - 1) / (s * 110), (100 * p) / (s * 90));
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  F(tc, 1, tcc + 1) {
    // LOG << "----------------" << endl;
    l n, m;
    cin >> n >> m;
    vl serve(n); F(i, 0, n) cin >> serve[i];
    vector<vll> ingrediends(n, vll(m));
    vvb used(n, vb(m));
    F(i, 0, n) F(j, 0, m) {
      l x; cin >> x;
      ingrediends[i][j] = f(x, serve[i]);
      used[i][j] = (ingrediends[i][j].first > ingrediends[i][j].second);
    }
    F(i, 0, n) {
      sort(all(ingrediends[i]));
    }
    l answer = 0;
    F(i, 0, m) {
      if (used[0][i]) continue;
      MergedIntervals q; q.add(ingrediends[0][i].first, ingrediends[0][i].second);
      F(j, 1, n) {
        MergedIntervals row;
        F(k, 0, m) if (not used[j][k]) row.add(ingrediends[j][k].first, ingrediends[j][k].second);
        q.intersect(row);
      }
      auto r = q.intervals();
      if (r.empty()) continue;
      answer++;
      l x = r[0].first;
      F(j, 1, n) {
        F(k, 0, m) if ((not used[j][k]) and
                       (ingrediends[j][k].first <= x) and
                       (x <= ingrediends[j][k].second)) {
          used[j][k] = true;
          break;
        }
      }
    }
    cout << "Case #" << tc << ": " << answer << lf;
  }
}
