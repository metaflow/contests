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
l MAX;
struct node;
using pnode = shared_ptr<node>;
struct edge {
  pnode to;
  l count = 0;
  l string_index, p, length;
};
struct node {
  vl at = vl(Z + 1);
  vector<edge> edges = vector<edge>(Z);
  vvl memo = vvl(Z);
};

void insert(pnode u, l x, size_t p, vvl& vs) {
  if (p >= vs[x].size()) return;
  auto& e = u->edges[vs[x][p]];
  if (not e.to) {
    e.to = make_shared<node>();
    e.count = 1;
    e.string_index = x;
    e.p = p;
    e.length = vs[x].size() - p;
  } else {
    e.count++;
    l n = min(e.length, (l)(vs[x].size() - p));
    for (l i = 1; i < n; i++) {
      l a = vs[e.string_index][i + e.p];
      l b = vs[x][i + p];
      if (a == b) continue;
      auto v = make_shared<node>();
      auto& e1 = v->edges[a];
      e1.to = e.to;
      e1.count = e.count - 1;
      // e1.s = e.s.substr(i);
      e1.string_index = e.string_index;
      e1.p = e.p + i;
      e1.length = e.length - i;
      e.to = v;
      // e.s.resize(i);
      e.length = i;
      insert(v, x, p + i, vs);
      return;
    }
    // s ends in the middle of the edge
    if (n < e.length) {
      auto v = make_shared<node>();
      l a = vs[e.string_index][n + e.p];
      auto& e1 = v->edges[a];
      e1.to = e.to;
      e1.count = e.count - 1;
      // e1.s = e.s.substr(n);
      e1.string_index = e.string_index;
      e1.p = e.p + n;
      e1.length = e.length - n;
      e.to = v;
      // e.s.resize(n);
      e.length = n;
    } else {
      insert(e.to, x, p + n, vs);
    }
  }
}

l count(pnode u, l at, l k) {
  if (at >= Z or k < 2) return 0;
  auto& e = u->edges[at];
  l& r = u->memo[at][k];
  if (r == 0) {
    r = count(u, u->at[at + 1], k);
    for (l j = 2; j <= min(e.count, k); j++) {
      r = max(r, j * (j - 1) * e.length / 2 +
              count(u, u->at[at + 1], k - j) +
              count(e.to, e.to->at[0], j));
    }
  }
  return r;
}

void process(pnode u) {
  l t = Z;
  u->at[Z] = Z;
  for (l i = Z - 1; i >= 0; i--) {
    if (u->edges[i].count > 1) {
      u->memo[i].resize(MAX);
      t = i;
      process(u->edges[i].to);
    }
    u->at[i] = t;
  }
}

l solve(vector<string>& v, l k) {
  // pnode root = make_shared<node>();
  // for (auto& s : v) insert(root, 0, 0, v);
  // return count(root, 0, k);
  return 0;
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
    MAX = k + 1;
    pnode root = make_shared<node>();
    vvl v(n);
    for (l i = 0; i < n; i++) {
      string s;
      cin >> s;
      v[i].resize(s.size());
      for (l j = 0; j < s.size(); j++) v[i][j] = s[j] - 'a';
      insert(root, i, 0, v);
    }
    process(root);
    cout << count(root, root->at[0], k) << '\n';
  }
}
