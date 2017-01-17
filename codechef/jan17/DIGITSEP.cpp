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

unordered_map<l, unordered_map<l, l>> memo;
vl digits;
l m;

l gcd(l a, l b) {
  while (b) {
    l t = b;
    b = a % b;
    a = t;
  }
  return a;
}

l lcm(l a, l b) {
  return a * b / gcd(a, b);
}

l index_of(const l n, const l x, const l y) {
  const l t = 1000;
  return (n * t  + x) * t + y;
}

l solve(l n, l x, l y, l g) {
  // LOG << n << ' ' << x << ' ' << g << endl;
  if (n == -1) {
    if (x > 0) return 0;
    return g;
  }
  if (y == 0) return 0;
  l id = index_of(n, x, y);
  if (memo[id].count(g)) return memo[id][g];
  l& best = memo[id][g];
  // best = 0;
  l mult = 1;
  l v = 0;
  l b = max((l)0, n - m + 1); // including: [b..n]
  for (l i = n; i >= b; i--) {
    v += mult * digits[i];
    mult *= 10;
    best = max(best, solve(i - 1, x - 1, y - 1, gcd(v, g)));
  }
  return best;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  while (tcc--) {
    memo.clear();
    l n; cin >> n;
    string s; cin >> s;
    assert((l)s.size() == n);
    digits.resize(n);
    for (l i = 0; i < n; i++) digits[i] = s[i] - '0';
    l x, y; cin >> m >> x >> y;
    cout << solve(n - 1, x + 1, y + 1, 0) << endl;
  }
}
