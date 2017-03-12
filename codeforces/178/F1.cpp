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
const l e0 = 1, e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;
#define ALL(x) begin(x), end(x)

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

vl P; // commont prefix of i and i - 1

l lcp(string& a, string& b) {
  l n = min(a.size(), b.size());
  for (l i = 0; i < n; i++) if (a[i] != b[i]) return i;
  return n;
}

vl score(l from, l to, l d) { // [from, to), d - existing lcp
  vl result(to - from + 1);
  if (to - from < 2) return result;
  l m = from + 1;
  for (l i = from + 2; i < to; i++) {
    if (P[i] < P[m]) m = i;
  }
  auto top = score(from, m, P[m]);
  auto bottom = score(m, to, P[m]);
  for (l i = 0; i <= m - from; i++) {
    for (l j = 0; j <= to - m; j++) {
      result[i + j] = max(result[i + j],
                          top[i] + bottom[j] + (i + j) * (i + j - 1) * (P[m] - d) / 2);

    }
  }
  return result;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, k;
  while (cin >> n >> k) {
    vector<string> ss(n);
    for (l i = 0; i < n; i++) cin >> ss[i];
    sort(ALL(ss));
    P.resize(n);
    for (l i = 1; i < n; i++) P[i] = lcp(ss[i], ss[i - 1]);
    auto v = score(0, n, 0);
    cout << v[k] << '\n';
  }
}
