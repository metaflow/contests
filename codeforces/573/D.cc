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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

struct bear {
  ll id, str, hpos;
};

struct region {
  ll from, to; // [from, to]
  ll delta;
  friend bool operator < (const region& a, const region& b) {
    // [1, 2] == [2, 3]
    return a.to < b.from;
  }
};

set<region> swaps;
vll W, Bl;
ll total;
ll triple_swap;

// [from, to), to - from must be even
ll bl_value(ll from, ll to) {
  //cerr << "bl " << from << " " << to << endl;
  return Bl[to] - Bl[from];
}

// [from, to)
ll w_value(ll from, ll to) {
  //cerr << "w " << from << " " << to << endl;
  return W[to] - W[from];
}

void insert_region(ll from, ll to);
void remove_region(ll from, ll to) {
  region r;
  r.from = from;
  r.to = to;
  auto p = swaps.equal_range(r);
  if (p.first == p.second) return;
  region q = *p.first;
  //cerr << "- [" << q.from << ", " << q.to << ") +" << q.value << " - " << q.removed_value << endl;
  total -= q.delta;
  swaps.erase(p.first);
  if (q.from < from) insert_region(q.from, from);
  if (q.to > to) insert_region(to, q.to);
}

void insert_region(ll from, ll to) {
  region r;
  r.from = from; r.to = to;
  auto p = swaps.equal_range(r);
  if (p.first != p.second) {
    region q = *p.first;
    remove_region(q.from, q.to);
    insert_region(min(q.from, r.from), max(q.to, r.to));
    return;
  }
  ll l = to - from;
  if (l % 2 == 0) {
    r.delta = bl_value(from, to) - w_value(from, to);
    if (from - 1 >= 0 && to + 1 < W.size()) {
      r.delta = max(r.delta, bl_value(from - 1, to + 1) - w_value(from - 1, to + 1));
    }
  } else {
    if (from == 0) {
      if (l == 1) {
        r.delta = bl_value(0, 2) - w_value(0, 2);
      } else {
        r.delta = triple_swap + bl_value(3, r.to) - w_value(0, r.to);
      }
    } else {
      r.delta = bl_value(from - 1, to) - w_value(from - 1, to);
      if (to + 1 < W.size()) {
        r.delta = max(r.delta, bl_value(from, to + 1) - w_value(from, to + 1));
      }
    }
  }
  //cerr << "+ [" << r.from << ", " << r.to << ") +" << r.delta << " - " << r.removed_value << endl;
  total += r.delta;
  swaps.insert(r);
}

void mark(ll x) {
  cerr << "mark " << x << endl;
  insert_region(x, x + 1);
}

void unmark(ll x) {
  cerr << "unmark " << x << endl;
  remove_region(x, x + 1);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, q;
  while (cin >> n >> q && n) {
    vector<bear> B(n), H(n);
    for (ll i = 0; i < n; i++) {
      cin >> B[i].str;
      B[i].id = i;
    }
    for (ll i = 0; i < n; i++) {
      cin >> H[i].str;
      H[i].id = i;
    }
    sort(B.begin(), B.end(), [] (const bear& a, const bear& b) {
      return a.str < b.str;
    });
    sort(H.begin(), H.end(), [] (const bear& a, const bear& b) {
      return a.str < b.str;
    });
    vll reverse_h(n);
    for (ll i = 0; i < n; i++) reverse_h[H[i].id] = i;
    vll reverse_b(n);
    for (ll i = 0; i < n; i++) reverse_b[B[i].id] = i;
    for (ll i = 0; i < n; i++) B[i].hpos = reverse_h[B[i].id];
    W.clear(); W.resize(n + 1);
    W[0] = 0;
    for (ll i = 0; i < n; i++) W[i + 1] = W[i] + B[i].str * H[i].str;
    Bl.clear(); Bl.resize(n + 1); // Bl[4] = [0,1] + [2,3] swaps
    Bl[1] = 0;
    Bl[0] = 0;
    for (ll i = 1; i < n; i++) Bl[i + 1] = Bl[i - 1] + B[i - 1].str * H[i].str + B[i].str * H[i - 1].str;
    if (n > 2) {
      triple_swap = max(
        B[0].str * H[2].str + B[1].str * H[0].str + B[2].str * H[1].str,
        B[0].str * H[1].str + B[1].str * H[2].str + B[2].str * H[0].str);
    }
    total = W[n];
    swaps.clear();
    for (ll i = 0; i < n; i++) if (B[i].hpos == i) mark(i);
    for (ll i = 0; i < q; i++) {
      ll a, b;
      cin >> a >> b; a--; b--;
      a = reverse_b[a];
      b = reverse_b[b];
      cerr << "swap " << a << " " << b << endl;
      // remove current blocks
      if (B[a].hpos == a) unmark(a);
      if (B[b].hpos == b) unmark(b);
      // add new
      swap(B[a].hpos, B[b].hpos);
      if (B[a].hpos == a) mark(a);
      if (B[b].hpos == b) mark(b);
      for (auto r : swaps) {
        cerr << r.from << ".." << r.to << endl;
      }
      cerr << i << ' ' << total << endl;
      cout << total << endl;
    }
  }
  // //cerr << "OK" << endl;
}
