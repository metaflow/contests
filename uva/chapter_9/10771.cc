#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

// RSQ for range [1, n]
struct fenwik_tree {
  vll tree;
  ll max_p;
  fenwik_tree(size_t n) {
    max_p = n;
    tree.resize(n + 1);
  };
  // sum of [1, p], O(log(max))
  ll read(ll p) {
    ll sum = 0;
    while (p) {
      sum += tree[p];
      p -= (p & -p);
    }
    return sum;
  }
  // O(log(max))
  void add(ll p, ll value) {
    while (p <= max_p) {
      tree[p] += value;
      p += (p & -p);
    }
  }
  // find lowest index with given sum, -1 if not found O(log(max))
  ll find(ll sum) {
    ll mask = max_p;
    while (true) {
      ll lower = (mask & -mask);
      if (lower == mask) break;
      mask -= lower;
    }
    ll p = 0;
    ll top = -1;
    while (mask != 0) {
      ll m = p + mask;
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
  ll n, m, k;
  while (cin >> n >> m >> k, n + m) {
    fenwik_tree f(n + m);
    for (ll i = 1; i <= n + m; i++) f.add(i, 1);
    vector<bool> v(n + m, false);
    for (ll i = n; i < n + m; i++) v[i] = true;
    ll p = 0;
    ll s = n + m;
    for (ll i = 0; i < n + m - 1; i++) {
      p = (p + k - 1) % s;
      ll at = f.find(p + 1) - 1;
      bool b = v[at];
      f.add(at + 1, -1);
      s--;
      p = (p + k - 1) % s;
      at = f.find(p + 1) - 1;
      v[at] = (v[at] != b);
      p++;
    }
    if (v[f.find(1) - 1]) {
      cout << "Keka" << endl;
    } else {
      cout << "Gared" << endl;
    }
  }
}
