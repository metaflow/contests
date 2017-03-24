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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m, s;
  while (cin >> n >> m >> s) {
    vll bugs(m);
    F(i, 0, m) {
      cin >> bugs[i].first;
      bugs[i].second = i;
    }
    vector<tuple<l,l,l>> students(n); // (ability, cost, id)
    F(i, 0, n) cin >> get<0>(students[i]);
    F(i, 0, n) { cin >> get<1>(students[i]); get<2>(students[i]) = i; }
    sort(ALL(bugs), greater<ll>());
    sort(ALL(students), greater<tuple<l,l,l>>());
    l x = binary_search_lower(1, m + 1, [&](l w) {
        priority_queue<l, vl, greater<l>> q;
        l total = 0;
        auto st = students.begin();
        for (l i = 0; i < m; i += w) {
          while (st != students.end() and get<0>(*st) >= bugs[i].first) {
            q.emplace(get<1>(*st));
            st++;
          }
          if (q.empty()) return false;
          total += q.top(); q.pop();
        }
        return total <= s;
      });
    if (x == m + 1) {
      cout << "NO\n";
    } else {
      vl answer(m);
      priority_queue<ll, vll, greater<ll>> q;
      auto st = students.begin();
      for (l i = 0; i < m; i += x) {
        while (st != students.end() and get<0>(*st) >= bugs[i].first) {
          q.emplace(get<1>(*st), get<2>(*st));
          st++;
        }
        l id = q.top().second; q.pop();
        F(j, i, min(i + x, m)) answer[bugs[j].second] = id + 1;
      }
      cout << "YES\n";
      F(i, 0, m) {
        if (i) cout << ' ';
        cout << answer[i];
      }
      cout << '\n';
    }
  }
}
