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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  while (tcc--) {
    l a, b;
    l answer = 0;
    cin >> a >> b;
    vl v(a * b);
    for (l i = 0; i < a * b; i++) cin >> v[i];
    vl acc(a * b + b + 1);
    for (l i = 0; i < acc.size() - 1; i++)
      acc[i + 1] = acc[i] + v[i % (a * b)];
    for (l i = 0; i < b; i++) {
      l one_sums = 0;
      for (l j = 0; j < a; j++) {
        if (acc[i + b * (j + 1)] - acc[i + b * j] > b / 2) one_sums++;
      }
      if (one_sums > a / 2) {
        answer = 1;
        break;
      }
    }
    cout << answer << '\n';
  }
}
