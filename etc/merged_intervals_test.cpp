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
const l e0=1, e3=1000, e5=100000, e6=e3*e3, e7=10*e6, e8=10*e7, e9=10*e8;
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

  void remove(l a, l b) {
    auto p = m.equal_range(make_pair(a, b));
    vll r;
    for (auto i = p.first; i != p.second; i++) r.emplace_back(*i);
    m.erase(p.first, p.second);
    for (auto i : r) {
      if (i.first < a) {
        m.emplace(make_pair(i.first, min(a, i.second) - 1));
      }
      if (i.second > b) {
        m.emplace(make_pair(max(b, i.first) + 1, i.second));
      }
    }
  }

  // returns all intervals intersecting with [a,b]
  // may be outside of [a, b]
  vll find(l a, l b) {
    vll r;
    auto p = m.equal_range(make_pair(a, b));
    for (auto i = p.first; i != p.second; i++) r.emplace_back(*i);
    return r;
  }

  bool intersectsWith(l a, l b) {
    auto p = m.equal_range(make_pair(a, b));
    return p.first != p.second;
  }

  // all intervals ordered
  vll intervals() {
    vll r;
    r.insert(r.begin(), m.cbegin(), m.cend());
    return r;
  }
};

default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
}

bool random_bool() {
  return random_in_range(0, 2) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size())];
  }
  return s;
}

struct operation {
  l type, a, b;
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l MAX = 100;
  F(op_count, 1, 10) {
    F(test, 0, 100) {
      vector<operation> ops;
      F(op, 0, op_count) {
        l o = random_in_range(0, 2);
        l a = random_in_range(0, MAX), b = random_in_range(a, MAX);
        ops.emplace_back(operation({o, a, b}));
      }
      vector<bool> real(100);
      MergedIntervals tree;
      for (auto o : ops) {
        switch (o.type) {
        case 0:
          tree.add(o.a, o.b);
          F(i, o.a, o.b + 1) real[i] = true;
          break;
        case 1:
          tree.remove(o.a, o.b);
          F(i, o.a, o.b + 1) real[i] = false;
          break;
        }
      }
      F(i, 0, MAX) {
        F(j, i, MAX) {
          bool f = false;
          F(k, i, j + 1) if (real[k]) { f = true; break; }
          auto intervals = tree.find(i, j);
          if (intervals.empty() != not f or f != tree.intersectsWith(i, j)) {
            for (auto o : ops) {
              cout << o.type << ' ' << o.a << ' ' << o.b <<'\n';
            }
            cout << i << ' ' << j << " -> " << intervals.size() << '\n';
            return 1;
          }
        }
      }
    }
  }
}
