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
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll k; cin >> k;
    fenwik_tree f(k);
    for (ll i = 1; i <= k; i++) f.add(i, 1);
    bool first = true;
    for (ll i = 0; i < k; i++) {
      if (!first) cout << " ";
      first = false;
      ll s; cin >> s; s++;
      ll a = f.find(s);
      assert(a != -1);
      f.add(a, -1);
      cout << a;
    }
    cout << endl;
  }
}
