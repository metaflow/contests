#include <bits/stdc++.h>
#undef LOCAL
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
bool local = true;
#else
bool local = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

struct Machine {
  l d, p, r, g;
};

ostream& operator << (ostream& o, const Machine& m) {
  return o << m.d << ' ' << m.p << ' ' << m.r << ' ' << m.g;
}

struct Sol {
  l d, m, g;
  l at(l x) {
    return (x - d) * g + m;
  }
};

ostream& operator << (ostream& o, const Sol& s) {
  return o << s.d << ' ' << s.m << ' ' << s.g;
}

l brute(vector<Machine>& mm, l c, l d) {
  // LOG << "brute" << endl;
  vector<Sol> ss;
  l best = c;
  for (auto m : mm) {
    for (auto s : ss) best = max(best, s.at(m.d - 1));
    // LOG << "best " << best << endl;
    if (m.p > best) continue;
    Sol p;
    p.d = m.d;
    p.g = m.g;
    p.m = best - m.p + m.r;
    ss.emplace_back(p);
  }
  for (auto s : ss) {
    // LOG << s << " = " << s.at(d) << endl;
    best = max(best, s.at(d));
  }
  return best;
}

// finds lowest x: f(x) = true, x within [a, b), b if f(b - 1) = false
l binary_search_lower(l a, l b, function<bool(l)> f) {
  l count = b - a;
  while (count > 0) {
    l step = count / 2;
    l m = a + step;
    if (not f(m)) {
      a = m + 1;
      count -= step + 1;
    } else {
      count = step;
    }
  }
  return a;
}

l cross(Sol a, Sol b) {
  l lo = max(a.d, b.d);
  l hi = lo;
  while (a.at(hi) > b.at(hi)) {
    lo = hi + 1;
    hi *= 2;
  }
  return binary_search_lower(lo, hi, [&](const l x) {
      return a.at(x) <= b.at(x);
    });
}

bool good(Sol a, Sol b, Sol c) {
  assert(a.g < b.g);
  assert(b.g < c.g);
  // LOG << "cross(a, b) " << cross(a, b) << endl;
  // LOG << "cross(b, c) " << cross(b, c) << endl;
  return cross(a, b) < cross(b, c);
}

l solve(vector<Machine>& mm, l start, l day) {
  // LOG << "solve" << endl;
  map<l, Sol> ss;
  l best = start;
  for (auto m : mm) {
    // LOG << m << endl;
    // LOG << "---------------" << endl;
    // for (auto s : ss) LOG << s << endl;
    if (not ss.empty()) best = max(best, ss.begin()->second.at(m.d - 1));
    while (ss.size() > 1) {
      auto a = ss.begin();
      auto b = next(a);
      l x = a->second.at(m.d - 1);
      l y = b->second.at(m.d - 1);
      if (x > y) break;
      LOG << "pop front" << endl;
      ss.erase(a);
      best = max(best, y);
    }
    if (m.p > best) {
      LOG << "cannot afford" << endl;
      continue;
    }
    Sol p;
    LOG << "best " << best << endl;
    p.d = m.d;
    p.g = m.g;
    p.m = best - m.p + m.r;
    if (ss.count(p.g)) {
      auto q = ss[p.g];
      if (q.at(m.d) >= p.at(m.d)) {
        LOG << "has same g - better" << endl;
        continue;
      }
      LOG << "has same g - worse" << endl;
      ss.erase(p.g);
    }

    auto q = ss.lower_bound(p.g);
    if (q != ss.begin() and q != ss.end()) {
      auto r = prev(q);
      if (!good(r->second, p, q->second)) {
        // LOG << "not good" << endl;
        continue;
      }
    }

    ss[p.g] = p;
    // LOG << "+ " << p << endl;
    while (1) {
      auto c = ss.find(p.g);
      if (c == ss.begin()) break;
      auto b = prev(c);
      if (b == ss.begin()) break;
      auto a = prev(b);
      if (good(a->second, b->second, c->second)) break;
      LOG << "remove below" << endl;
      ss.erase(b);
    }
    while (1) {
      auto a = ss.find(p.g);
      auto b = next(a);
      if (b == ss.end()) break;
      auto c = next(b);
      if (c == ss.end()) break;
      if (good(a->second, b->second, c->second)) break;
      // LOG << "remove above" << endl;
      ss.erase(b);
    }
  }
  // LOG << "---------------" << endl;
  // for (auto s : ss) LOG << s << endl;
  for (auto s : ss) best = max(best, s.second.at(day));
  return best;
}

default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
}

double random_double() {
  return uniform_real_distribution<double>(0, 1)(source);
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

void test() {
  local = false;
  F(n, 1, 10) {
    F(i, 10, 100) {
      F(tc, 0, 10000) {
        vector<Machine> mm(n);
        l day = 0;
        for (auto& m : mm) {
          m.d = random_in_range(1, i);
          day = max(day, m.d);
          m.r = random_in_range(1, i);
          m.p = m.r + random_in_range(1, i);
          m.g = random_in_range(1, i);
        }
        sort(all(mm), [](const Machine& a, const Machine& b) {
            return a.d < b.d;
          });
        l start = random_in_range(1, 1000);
        day += random_in_range(0, 10);
        l a = brute(mm, start, day);
        l b = solve(mm, start, day);
        if (a != b) {
          cout << a << " <> " << b << lf;
          cout << n << ' ' << start << ' ' << day << lf;
          for (auto m : mm) cout << m.d << ' ' << m.p << ' ' << m.r << ' ' << m.g << lf;
          return;
        }
      }
    }
  }
  cout << "PASSED" << endl;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // test();
  // return 0;
  // solution
  l n, c, d;
  l tc = 0;
  while (cin >> n >> c >> d, n) {
    tc++;
    vector<Machine> mm(n);
    F(i, 0, n) cin >> mm[i].d >> mm[i].p >> mm[i].r >> mm[i].g;
    sort(all(mm), [](const Machine& a, const Machine& b) {
        return a.d < b.d;
      });
    // cout << "Case " << tc << ": " << brute(mm, c, d) << lf;
    cout << "Case " << tc << ": " << solve(mm, c, d) << lf;
  }
}
