#if defined(LOCAL)
#define PROBLEM_NAME "a"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define I(x, ...) (x)
// TODO: add macro to disable L, e.g. _L()
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define I(x, ...) (x)
#define C(x, ...) ;
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

struct node;
using pnode = shared_ptr<node>;
string ans;
struct node {
  vector<pnode> adj = vector<pnode>(26);
  l size; // subtree
  l update_size() {
    size = 1;
    for (auto& a : adj) if (a) size += a->update_size();
    return size;
  }
  void find(l k) {
    if (k == 0) return;
    F(i, 0, adj.size()) {
      if (not adj[i]) continue;
      if (adj[i]->size < k) {
        k -= adj[i]->size;
        continue;
      }
      ans.push_back(char('a' + i));
      adj[i]->find(k - 1);
      break;
    }
  }
};

vl stovl(string const& s) {
  vl v(s.size());
  F(i, 0, v.size()) v[i] = s[i] - 'a';
  return v;
}

void sort_suffix_array(vl& sa, vl& rank, l k) {
  l n = sa.size();
  vl counts(max(n, (l)300));
  F(i, 0, n) {
    l p = 0;
    if (i + k < n) p = rank[i + k];
    counts[p]++;
  }
  l s = 0;
  for (size_t i = 0; i < counts.size(); i++) {
    l t = counts[i];
    counts[i] = s;
    s += t;
  }
  vl updated_sa(n);
  for (auto i : sa) {
    l p = 0;
    if (i + k < n) p = rank[i + k];
    updated_sa[counts[p]] = i;
    counts[p]++;
  }
  swap(sa, updated_sa);
}

// TODO: update signature
vl build_suffix_array(string const& s) {
  l n = s.size();
  vl sa(n);
  vl rank(n);
  F(i, 0, n) {
    rank[i] = s[i];
    sa[i] = i;
  }
  for (l k = 1; k < n; k = k << 1) {
    sort_suffix_array(sa, rank, k);
    sort_suffix_array(sa, rank, 0);
    vl updated_rank(rank.size());
    l r = 0;
    updated_rank[sa[0]] = r;
    F(i, 1, n) {
      if (rank[sa[i]] != rank[sa[i - 1]] ||
          rank[sa[i] + k] != rank[sa[i - 1] + k]) r++;
      updated_rank[sa[i]] = r;
    }
    swap(rank, updated_rank);
    if (rank[sa[n - 1]] == n - 1) break;
  }
  return sa;
}

vl build_lcp(string &s, vl &sa) {
  l n = sa.size();
  vl lcp(n), plcp(n);
  vl p(n);
  p[sa[0]] = -1;
  F(i, 1, n) p[sa[i]] = sa[i - 1];
  l w = 0;
  F(i, 0, n) {
    if (p[i] == -1) { plcp[i] = 0; continue; }
    while (s[i + w] == s[p[i] + w] && i + w + 1 < n) w++;
    plcp[i] = w;
    if (w) --w;
  }
  F(i, 0, n) lcp[i] = plcp[sa[i]];
  return lcp;
}

// TODO: add trie template
// TODO: fix atcoder parser
void solve(istream& cin, ostream& cout) {
  string s; cin >> s;
  l n = s.size();
  // TODO: make SA builder treat last char as lowest
  s += "@";
  l k; cin >> k;
  auto sa = build_suffix_array(s);
  auto lcp = build_lcp(s, sa);
  F(i, 0, sa.size()) {
    l p = sa[i];
    l x = max(l(0), n - p - lcp[i]);
    if (I(x, k) >= k) {
      I("out", p, lcp[i] + k - 1);
      cout << s.substr(p, lcp[i] + k) << lf;
      break;
    }
    k -= x;
  }
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
