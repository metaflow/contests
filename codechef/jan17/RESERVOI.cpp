#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <string>

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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  while (tcc--) {
    l n, m; cin >> n >> m;
    string current, next(m, 'A');
    bool ok = true;
    for (l i = 0; i <= n; i++) {
      swap(current, next);
      if (i == n) {
        next = string(m, 'B');
      } else {
        cin >> next;
      }
      // LOG << current << endl << next << endl << endl;
      for (l j = 0; j < m; j++) {
        if (current[j] == 'B') {
          if ((next[j] == 'A') or (next[j] == 'W')) ok = false;
        } else if (current[j] == 'W') {
          if ((j == 0) or (j == m - 1) or
                      (current[j - 1] == 'A') or (current[j + 1] == 'A') or
                      (next[j] == 'A')) {
            ok = false;
          }
        }
      }
    }
    cout << (ok ? "yes" : "no") << endl;
  }
}
