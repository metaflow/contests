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

using lll = tuple<ll, ll ,ll>;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n) {
    vector<lll> legs(n); // l, d, index
    for (ll i = 0; i < n; i++) cin >> get<0>(legs[i]);
    for (ll i = 0; i < n; i++) cin >> get<1>(legs[i]);
    sort(legs.begin(), legs.end(), [] (const lll& a, const lll& b) {
      return get<1>(a) < get<1>(b);
    });
    fenwik_tree sum(n), left(n);
    for (ll i = 0; i < n; i++) {
      get<2>(legs[i]) = i + 1;
      sum.add(i + 1, get<1>(legs[i]));
      left.add(i + 1, 1);
    }
    sort(legs.begin(), legs.end(), greater<lll>());
    auto p = legs.begin();
    ll best = INF;
    ll removed = 0;
    while (p != legs.end()) {
      auto u = p;
      ll cost = removed;
      while (u != legs.end() && get<0>(*u) == get<0>(*p)) {
        removed += get<1>(*u);
        sum.add(get<2>(*u), -get<1>(*u));
        left.add(get<2>(*u), -1);
        u++;
      }
      ll m = u - p;
      if (n > 2 * m - 1) {
        ll at = left.find(n - 2 * m + 1);
        if (at > 0) cost += sum.read(at);
      }
      best = min(best, cost);
      n -= m;
      p = u;
    }
    cout << best << endl;
  }
}
