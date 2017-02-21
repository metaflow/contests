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

const l MAX = 1024;
int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, k, x;
  while (cin >> n >> k >> x) {
    vl v(MAX), vc(MAX);
    for (l i = 0; i < n; i++) {
      l a; cin >> a; v[a]++;
    }
    for (l i = 0; i < k; i++) {
      l t = 0;
      vc = v;
      for (l j = 0; j < MAX; j++) {
        l d;
        if (t % 2) {
          d = v[j] / 2;
        } else {
          d = (v[j] + 1) / 2;
        }
        vc[j] -= d;
        vc[j ^ x] += d;
        t += v[j];
      }
      swap(v, vc);
    }
    l top = 0, bot = MAX;
    for (l i = 0; i < MAX; i++) if (v[i]) { bot = i; break; }
    for (l i = MAX - 1; i >= 0; i--) if (v[i]) { top = i; break; }
    cout << top << ' ' << bot << '\n';
  }
}
