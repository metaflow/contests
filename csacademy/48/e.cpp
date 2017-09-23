#if defined(LOCAL)
#define PROBLEM_NAME "e"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#include <bits/stdc++.h>
#endif

using namespace std;
using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define max(a,b)({__typeof__(a)x=(a);__typeof__(b)y=(b);x>y?x:y;})
#define min(a,b)({__typeof__(a)x=(a);__typeof__(b)y=(b);x<y?x:y;})

struct Edge {
  l to, id, from;
};

struct Graph {
  l v_count, e_count;
  vector<vector<Edge>> adj;
  vector<Edge> edges;

  Graph(l n) {
    v_count = n;
    adj.resize(n);
    e_count = 0;
  }

  void add_undirected(l a, l b) {
    Edge ab; ab.id = e_count; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    Edge ba; ba.id = e_count; ba.from = b; ba.to = a;
    adj[b].emplace_back(ba);
    e_count++;
    edges.emplace_back(ab);
  }

  void add_directed(l a, l b) {
    Edge ab; ab.id = e_count; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    e_count++;
    edges.emplace_back(ab);
  }
};

struct SCC {
  vl age, lowlink, component;
  vb art;
  l time, count;
  stack<l> path;

  SCC(Graph& g) {
    age.resize(g.v_count);
    art.resize(g.v_count);
    lowlink.resize(g.v_count);
    component.resize(g.v_count, -1);
    time = 0;
    count = 0;
    F(i, 0, g.v_count) if (not age[i]) dfs(g, i);
  }

  void dfs(Graph& g, l a) {
    time++;
    age[a] = lowlink[a] = time;
    path.push(a);
    for (auto e : g.adj[a]) {
      l b = e.to;
      if (not age[b]) dfs(g, b);
      if (lowlink[b] > age[a]) art[a] = true;
      lowlink[a] = min(lowlink[a], lowlink[b]);
    }
    if (lowlink[a] == age[a]) {
      while (1) {
        l t = path.top(); path.pop();
        lowlink[t] = INF;
        component[t] = count;
        if (t == a) break;
      }
      count++;
    }
  }
};

// tuple hash
namespace std { namespace {
    template <class T>
    inline void hash_combine(std::size_t& seed, T const& v) {
      seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }
    template <class T, size_t Index = std::tuple_size<T>::value - 1>
    struct HashValueImpl {
      static void apply(size_t& seed, T const& tuple) {
        HashValueImpl<T, Index-1>::apply(seed, tuple);
        hash_combine(seed, std::get<Index>(tuple));
      }
    };
    template <class T>
    struct HashValueImpl<T,0> {
      static void apply(size_t& seed, T const& tuple) {
        hash_combine(seed, std::get<0>(tuple));
      }
    }; } // namespace
  template <typename ... TT>
  struct hash<std::tuple<TT...>> {
    size_t operator()(std::tuple<TT...> const& tt) const {
      size_t seed = 0;
      HashValueImpl<std::tuple<TT...> >::apply(seed, tt);
      return seed;
    }
  };}

l sign(l n) {
  if (n < 0) return -1;
  if (n == 0) return 0;
  return 1;
}

// conruent modulo, works for negative
l cong(l x, l mod) {
  return (x % mod + mod) % mod;
}

// (a * b) % mod, safe for l near max
l mult_mod(l a, l b, l mod) {
  l x = 0;
  while (b) {
    if (b % 2) x = (x + a) % mod;
    a = (a * 2) % mod;
    b /= 2;
  }
  return x;
}

// (base^power) % mod, safe for l near max
l pow_mod(l base, l power, l mod) {
  l r = 1;
  while (power) {
    if (power % 2) r = mult_mod(r, base, mod);
    base = mult_mod(base, base, mod);
    power /= 2;
  }
  return r;
}

l divup(l a, l b) { // ceil div
  return (a + b - 1) / b;
}

// return gcd(a, b) and set x, y: a * x + b * y = gcd(a, b)
l extended_euclid(l a, l b, l& x, l& y) {
  if (b == 0) { x = 1; y = 0; return a; }
  l d = extended_euclid(b, a % b, x, y);
  l t = y;
  y = x - (a / b) * y;
  x = t;
  return d;
}

// return b: a * b = 1 (mod n)
l inverse_mod(l a, l n) {
  l x, y;
  l d = extended_euclid(a, n, x, y);
  if (d != 1) return 0;
  return cong(x, n);
}

// single combintions k from n
l nCr(l n, l k, l mod) {
  l a = 1;
  for (l i = n; i > n - k; i--) a = mult_mod(a, i, mod);
  l b = 1;
  F(i, 1, k + 1) b = mult_mod(b, i, mod);
  b = inverse_mod(b, mod);
  return mult_mod(a, b, mod);
}

// precompute all combinations up to (n n)
vvl combinations(l n, l mod) {
  vvl c(n + 1, vl(n + 1));
  F(i, 0, n) {
    c[i][0] = 1;
    F(j, 1, i + 1) {
      c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
    }
  }
  return c;
}



const l MOD = e9 + 7;
const l MOD1 = e9 + 21;
const l MOD2 = e9 + 33;

void solve(istream& cin, ostream& cout) {
  l n, k; cin >> n >> k;
  vector<string> ss(n); F(i, 0, n) cin >> ss[i];
  unordered_map<tuple<l, l>, vl> hash_to_id;
  l m1 = 1, m2 = 1;
  l z = 255;
  F(i, 0, k - 2) {
    m1 = cong(m1 * z, MOD1);
    m2 = cong(m2 * z, MOD2);
  }
  L(m1, m2);
  F(i, 0, n) {
    l h1 = 0, h2 = 0;
    F(j, 0, k - 1) {
      h1 = (h1 * z + ss[i][j]) % MOD1;
      h2 = (h2 * z + ss[i][j]) % MOD2;
    }
    // L(h1, h2);
    hash_to_id[make_tuple(h1, h2)].emplace_back(i);
  }
  Graph g(n);
  // L("----");
  for (auto kv : hash_to_id) {
    auto h = kv.first;
    for (auto i : kv.second) {
      l h1, h2; tie(h1, h2) = h;
      h1 = cong((h1 - m1 * ss[i][0]) * z + ss[i][k - 1], MOD1);
      h2 = cong((h2 - m2 * ss[i][0]) * z + ss[i][k - 1], MOD2);
      // L(h1, h2);
      for (auto j : hash_to_id[make_tuple(h1, h2)]) {
        g.add_directed(i, j);
      }
    }
  }
  SCC scc(g);
  L(scc.component);
  L(scc.art);
  l start = -1;
  if (scc.count == 1) {
    start = 0;
  } else {
    l root = scc.count - 1;
    F(i, 0, n) if (scc.component[i] == root and scc.art[i]) start = i;
    if (start == -1) { cout << -1 << lf; return; }
    for (auto e : g.adj[start]) if (scc.component[e.to] == root) {
        start = e.to;
        break;
      }
  }
  vl path;
  vb visited(n);
  while (1) {
    path.emplace_back(start);
    visited[start] = true;
    l next = start;
    for (auto e : g.adj[start]) {
      if (not visited[e.to]) { next = e.to; break;}
    }
    if (next == start) break;
    swap(next, start);
  }
  if (path.size() != n) {
    cout << -1 << lf;
    return;
  }
  F(i, 0, n - 1) cout << ss[path[i]][0];
  cout << ss[path[n - 1]] << lf;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
