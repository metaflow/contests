//time 0:40:00
#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

// intervals are inclusive [a, b]
// e.g. [1, 2] + [2, 3] -> [1, 3]
// [1, 4] - [2, 3] -> [1], [4]
// and find([4, 7]) -> ([1, 4], [5, 6], [7, 11])
class interval_tree {
private:
  struct intervals_key {
    bool operator() (const ii& a, const ii& b) {
      return a.second < b.first;
   };
  };
  set<ii, intervals_key> m;
  friend ostream& operator << (ostream& s, const interval_tree& v) {
    for (auto ii = v.m.cbegin(); ii != v.m.cend(); ii++) {
      s << "[" << ii->first << ", " << ii->second << "] ";
    }
    return s;
  }
public:
  void add(int a, int b) {
    vii r;
    auto p = m.equal_range(make_pair(a, b));
    for (auto ii = p.first; ii != p.second; ii++) r.emplace_back(*ii);
    m.erase(p.first, p.second);
    for (auto ii : r) {
      a = min(a, ii.first);
      b = max(b, ii.second);
    }
    m.emplace(make_pair(a, b));
  }

  void remove(int a, int b) {
    auto p = m.equal_range(make_pair(a, b));
    vii r;
    for (auto ii = p.first; ii != p.second; ii++) r.emplace_back(*ii);
    m.erase(p.first, p.second);
    for (auto ii : r) {
      if (ii.first < a) {
        m.emplace(make_pair(ii.first, min(a, ii.second) - 1));
      }
      if (ii.second > b) {
        m.emplace(make_pair(max(b, ii.first) + 1, ii.second));
      }
    }
  }

  vii find(int a, int b) {
    vii r;
    auto p = m.equal_range(make_pair(a, b));
    for (auto i = p.first; i != p.second; i++) r.emplace_back(*i);
    return r;
  }

  vii keys() {
    vii r;
    r.insert(r.begin(), m.cbegin(), m.cend());
    return r;
  }
};

const l MAX_LOG = 31;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m;
  while (cin >> n >> m) {
    vector<interval_tree> bit_intervals(MAX_LOG);
    vl L(m), R(m), Q(m);
    for (l i = 0; i < m; i++) {
      cin >> L[i] >> R[i] >> Q[i];
      L[i]--;
    }
    for (l i = 0; i < m; i++) {
      l t = Q[i];
      for (l j = 0; j < MAX_LOG; j++) {
        if (t % 2) bit_intervals[j].add(L[i], R[i]);
        t /= 2;
      }
    }
    bool yes = true;
    for (l i = 0; i < m; i++) {
      l t = Q[i];
      for (l j = 0; j < MAX_LOG; j++) {
        if (t % 2 == 0) {
          auto v = bit_intervals[j].find(L[i], R[i]);
          if (v.size() == 1 && v[0].first <= L[i] && v[0].second >= R[i]) {
            yes = false;
          }
        }
        t /= 2;
      }
    }
    if (yes) {
      vl answer(n);
      l t = 1;
      for (l j = 0; j < MAX_LOG; j++) {
        for (auto bi : bit_intervals[j].keys()) {
          for (l i = bi.first; i < bi.second; i++) answer[i] += t;
        }
        t *= 2;
      }
      cout << "YES" << endl;
      bool first = true;
      for (auto i : answer) {
        if (!first) cout << " ";
        first = false;
        cout << i;
      }
      cout << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
