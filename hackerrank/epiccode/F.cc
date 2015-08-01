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

const ll MOD = 1000000007;
const int BUCKET = 50;

struct node {
  ll sum = 0;
  vii pending;
  vll values;
};

vector<node> tree;

// [from, to)
void build_tree(int p, int from, int to) {
  tree.resize(max(p + 1, int(tree.size())));
  if (to - from <= BUCKET) {
    tree[p].values.resize(BUCKET);
    return;
  }
  int m = (from + to) / 2;
  p <<= 1;
  build_tree(p, from, m);
  build_tree(p + 1, m, to);
}

vll es, cs;

// sum of [f, t)
ll sum(ll f, ll t) {
  // assert(t < cs.size());
  return cs[t] - cs[f] + MOD;
}

void add(int p, int f, int t, int x, int y) {
  // assert(p < tree.size());
  if (t <= x || y <= f) return;
  tree[p].pending.emplace_back(x, y);
}

ll query(int p, int f, int t, int x, int y) {
  if (t <= x || y <= f) return 0;
  auto &node = tree[p];
  int np = p << 1;
  int m = (f + t) / 2;
  // assert(p < tree.size());

  if (!node.pending.empty()) {
    if (t - f <= BUCKET) {
      for (auto xy : node.pending) {
        for (int i = max(f, xy.first); i < min(t, xy.second); i++) {
          node.values[i - f] += es[i - xy.first];
          node.sum += es[i - xy.first];
        }
      }
      node.sum = node.sum % MOD;
    } else {
      for (auto xy : node.pending) {
        int a = max(f - xy.first, 0);
        node.sum += sum(a, xy.second - xy.first);
        add(np, f, m, xy.first, min(xy.second, m));
        add(np + 1, m, t, xy.first, min(xy.second, t));
      }
      node.sum = node.sum % MOD;
    }
    node.pending.clear();
  }
  if (f >= x && t <= y) {
    // if (node.sum == -1) {
    //   node.sum = (query(np, f, m, f, m) +
    //               query(np + 1, m, t, m, t)) % MOD;
    // }
    return node.sum;
  }
  if (t - f <= BUCKET) {
    ll r = 0;
    for (int i = max(f, x); i < min(t, y); i++) {
      r += node.values[i - f];
    }
    return r % MOD;
  }
  return (query(np, f, m, x, min(y, m)) +
          query(np + 1, m, t, x, min(y, t))) % MOD;
}

int main() {
  // ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, q;
  // cin >> n >> q;
  scanf("%lld%lld", &n, &q);
  cs.resize(n + 1);
  es.resize(n + 1);
  for (ll i = 1; i <= n; i++) {
    cs[i] = (cs[i - 1] + i * (i + 1)) % MOD;
    es[i - 1] = (i * (i + 1)) % MOD;
  }
  build_tree(1, 0, n);
  while (q--) {
    ll t, x, y;
    // cin >> t >>
    scanf("%lld%lld%lld", &t, &x, &y);
    if (t == 1) {
      add(1, 0, n, x - 1, y);
    } else {
      printf("%lld\n", query(1, 0, n, x - 1, y));
      // cout << query(1, 0, n, x - 1, y) << endl;
    }
  }
}
