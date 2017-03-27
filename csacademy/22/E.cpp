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

// RSQ for range [1, n]
struct fenwik_tree {
  vl tree;
  l max_p;
  fenwik_tree(size_t n) {
    max_p = n;
    tree.resize(n + 1);
  };
  // sum of [1, p], O(log(max))
  l read(l p) {
    l sum = 0;
    while (p) {
      sum += tree[p];
      p -= (p & -p);
    }
    return sum;
  }
  // O(log(max))
  void add(l p, l value) {
    while (p <= max_p) {
      tree[p] += value;
                    p += (p & -p);
    }
  }
  // find lowest index with given sum, -1 if not found O(log(max))
  l find(l sum) {
    l mask = max_p;
    while (true) {
      l lower = (mask & -mask);
      if (lower == mask) break;
      mask -= lower;
    }
    l p = 0;
    l top = -1;
    while (mask != 0) {
      l m = p + mask;
      if (m <= max_p) {
        if (sum == tree[m]) top = m;
        if (sum > tree[m]) {
          p = m;
          sum -= tree[m];
        }
      }
      mask >>= 1;
    }
    if (sum != 0) return top;
    return p;
  }
};


int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, k;
  while (cin >> n >> k) {
    LOG << "------\n";
    vl v(n); F(i, 0, n) cin >> v[i];
    auto cmp = [&](const l& a, const l& b) {
      if (v[a] != v[b]) return v[a] < v[b];
      return b < a;
    };
    priority_queue<l, vl, decltype(cmp)> q(cmp);
    F(i, 0, n) q.emplace(i);
    fenwik_tree ft(n);
    vb taken(n);
    vl answer = v;
    l t = 0;
    F(i, 0, n) {
      while (taken[t]) t++;
      l j = t;
      while ((not q.empty()) and (q.top() - ft.read(q.top() + 1)) > k) q.pop();
      if (not q.empty()) {
        j = q.top(); q.pop();
        LOG << "- " << (j - ft.read(j + 1)) << '\n';
        k -= (j - ft.read(j + 1));
      }
      ft.add(j + 1, 1);
      answer[i] = v[j];
      taken[j] = true;
    }
    F(i, 0, n) {
      if (i) cout << ' ';
      cout << answer[i];
    }
    cout << '\n';
  }
}
