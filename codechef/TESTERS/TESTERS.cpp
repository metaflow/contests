#if defined(LOCAL)
const double _max_double_error = 1e-10;
#define PROBLEM_NAME "TESTERS"
#include "prettyprint.h"
#include "testutils.h"
#endif
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

struct BIT {
  vl tree;
  l max_p;
  BIT(size_t n) {
    max_p = n;
    tree.resize(n + 1);
  };
  // sum of [1, p], O(log(max))
  l get(l p) {
    if (p <= 0) return 0;
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

const l MAX_PRIME = 2000;
// returns vector of v[i] = smallest prime divisor of i or 1
vl sieve_primes(vl& primes) {
  vl next_div(MAX_PRIME, 1);
  for (l i = 2; i < MAX_PRIME; i++) {
    if (next_div[i] != 1) continue;
    primes.emplace_back(i);
    for (l j = i; j < MAX_PRIME; j += i) if (next_div[j] == 1) next_div[j] = i;
  }
  return next_div;
}

vl factorize_to_primes(l n, vl& primes, vl& next_div) {
  auto p = primes.begin();
  vl result;
  while (n >= MAX_PRIME and p != primes.end()) {
    while (n % *p == 0) { result.emplace_back(*p); n /= *p; }
    p++;
  }
  if (n >= MAX_PRIME) {
    result.emplace_back(n);
    n = 1;
  }
  while (n != 1) {
    result.emplace_back(next_div[n]);
    n /= next_div[n];
  }
  return result;
}

struct node;
using pnode = shared_ptr<node>;
using graph = vector<pnode>;

struct node {
  l id, value;
  bool visited;
  vector<pnode> adjusted;
  l subtreeSize = 1; bool blocked;
  pnode parent;
};

l divisorsSum(vl& factors) {
  vl v;
  v.emplace_back(1);
  l p = 0;
  while (p < factors.size()) {
    l a = factors[p];
    l k = v.size();
    l m = 1;
    while (p < factors.size() and factors[p] == a) {
      m *= a;
      F(i, 0, k) v.emplace_back(v[i] * m);
      p++;
    }
  }
  l t = 0;
  for (auto x : v) t += x * x;
  return t;
}

// add bool blocked and subtreeSize to node
void dfsSubtreeSize(pnode u) {
  u->subtreeSize = 1;
  for (auto v : u->adjusted) {
    if (v->blocked or u->parent == v) continue;
    v->parent = u;
    dfsSubtreeSize(v);
    u->subtreeSize += v->subtreeSize;
  }
}

void dfs(pnode u, l x, l depth, vll& paths) {
  x += u->value;
  paths.emplace_back(make_pair(x, depth));
  for (auto v : u->adjusted) {
    if (v->blocked or v == u->parent) continue;
    v->parent = u;
    dfs(v, x, depth + 1, paths);
  }
}

l solveFor(pnode root, l n) {
  root->parent = nullptr;
  BIT sums(2 * n), counts(2 * n);
  l r = 0;
  if (root->value > 0) r++;
  for (auto u : root->adjusted) {
    if (u->blocked) continue;
    vll paths;
    u->parent = root;
    dfs(u, 0, 1, paths);
    for (auto p : paths) {
      l i = -p.first - root->value + n;
      r += (counts.get(2 * n) - counts.get(i - 1)) * (1 + p.second) +
        (sums.get(2 * n) - sums.get(i - 1));
      if (p.first + root->value >= 0) r += 1 + p.second;
    }
    for (auto p : paths) {
      sums.add(p.first + n, p.second);
      counts.add(p.first + n, 1);
    }
  }
  return r;
}

l decompose(pnode u) {
  u->parent = nullptr;
  dfsSubtreeSize(u);
  l total = u->subtreeSize;
  queue<pnode> q;
  q.emplace(u);
  l best = total;
  pnode centroid = u;
  while (!q.empty()) {
    auto v = q.front(); q.pop();
    l t = total - v->subtreeSize;
    for (auto w : v->adjusted) {
      if (w->blocked or w == v->parent) continue;
      t = max(t, w->subtreeSize);
      q.emplace(w);
    }
    if (t < best) {
      centroid = v;
      best = t;
    }
  }
  l answer = solveFor(centroid, best + 1); // + 1 as root is also participating
  centroid->blocked = true;
  for (auto v : centroid->adjusted) {
    if (not v->blocked) answer += decompose(v);
  }
  return answer;
}

void solve(istream& in, ostream& out) {
  // solution
  vl primes;
  vl next_div = sieve_primes(primes);
  l n;
  in >> n;
  graph g(n);
  F(i, 0, n) {
    debug(i, i);
    g[i] = make_shared<node>();
    g[i]->id = i + 1;
  }
  F(i, 0, n - 1) {
    l a, b; in >> a >> b; a--; b--;
    g[a]->adjusted.emplace_back(g[b]);
    g[b]->adjusted.emplace_back(g[a]);
  }
  F(i, 0, n) {
    l x; cin >> x;
    auto ff = factorize_to_primes(x, primes, next_div);
    g[i]->value = ((divisorsSum(ff) % 2) * 2 - 1);
  }
  out << decompose(g[0]) << lf;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
