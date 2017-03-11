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

const l Z = 26;
struct node;
using pnode = shared_ptr<node>;
struct edge {
  pnode to;
  l count = 0, length = 1;
};
struct node {
  map<l, edge> edges;
  pnode parent;
  l p;
  unordered_map<l, l> memo;
};

void insert(pnode u, string& s, size_t p) {
  if (p >= s.size()) return;
  l v = s[p] - 'a';
  auto& e = u->edges[v];
  if (not e.to) {
    e.to = make_shared<node>();
    e.to->p = v;
    e.to->parent = u;
  }
  e.count++;
  insert(e.to, s, p + 1);
}

void compact(pnode u) {
  if (u->parent) {
    l next = -1;
    for (l i = 0; i < Z; i++) {
      if (u->edges[i].count) next = i;
    }
    auto& pe = u->parent->edges[u->p];
    if (next > -1 && pe.count == u->edges[next].count) {
      auto v = u->edges[next].to;
      pe.length += u->edges[next].length;
      pe.to = v;
      v->parent = u->parent;
      v->p = u->p;
      compact(v);
      return;
    }
  }
  for (auto& e : u->edges) if (e.second.to) compact(e.second.to);
}

l count(pnode u, l at, l k) {
  if (at >= Z or k < 2) return 0;
  auto& e = u->edges[at];
  if (e.count < 2) return count(u, at + 1, k);
  l key = k * Z + at;
  if (u->memo.count(key) == 0) {
    l r = count(u, at + 1, k);
    for (l j = 2; j <= min(e.count, k); j++) {
      r = max(r, j * (j - 1) * e.length / 2 +
              count(e.to, 0, j) + count(u, at + 1, k - j));
    }
    u->memo[key] = r;
  }
  return u->memo[key];
}

l solve(vector<string>& v, l k) {
  pnode root = make_shared<node>();
  for (auto& s : v) insert(root, s, 0);
  compact(root);
  return count(root, 0, k);
}


l popcnt(l value) { return __builtin_popcount(value); }
bool bit_set(l mask, l i) { return mask & (e0 << i); }

l prefix(string& a, string& b) {
  l n = min(a.size(), b.size());
  for (l i = 0; i < n; i++) {
    if (a[i] != b[i]) return i;
  }
  return n;
}

l solve_brute(vector<string>& v, l k) {
  l n = v.size();
  l r = 0;
  for (l m = 1; m < (e0 << n); m++) {
    l t = 0;
    if (popcnt(m) != k) continue;
    for (l i = 0; i < n; i++) {
      if (not bit_set(m, i)) continue;
      for (l j = i + 1; j < n; j++) {
        if (bit_set(m, j)) t += prefix(v[i], v[j]);
      }
    }
    r = max(r, t);
  }
  return r;
}


default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b)(source);
}

bool random_bool() {
  return random_in_range(0, 1) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "abcdefghijklmnopqrstuvwxyz";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size() - 1)];
  }
  return s;
}


void test() {
  for (l n = 1; n < 10; n++) {
    for (l i = 1; i < 10; i++) {
      for (l k = 1; k <= n; k++) {
        for (l tc = 0; tc < 1000; tc++) {
          vector<string> v(n);
          for (l j = 0; j < n; j++) v[j] = random_string(random_in_range(1, i));
          l a = solve(v, k);
          l b = solve(v, k);
          if (a != b) {
            LOG << n << ' ' << k << '\n';
            for (auto s : v) LOG << s << '\n';
            LOG << a << " <> " << b << '\n';
            return;
          }
        }
      }
    }
  }
  LOG << "OK\n";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // test();
  // return 0;
  l n, k;
  while (cin >> n >> k) {
    pnode root = make_shared<node>();
    for (l i = 0; i < n; i++) {
      string s; cin >> s;
      insert(root, s, 0);
    }
    compact(root);
    cout << count(root, 0, k) << '\n';
  }
}
