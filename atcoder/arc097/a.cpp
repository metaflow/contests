#if defined(LOCAL)
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define I(x, ...) (x)
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define I(x, ...) (x)
#define C(x, ...) ;
#endif
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <math.h>
#include <limits>
#include <numeric>
#include <queue>
#include <memory>

using namespace std;
using vi = vector<int>; using vvi = vector<vi>; using vvvi = vector<vvi>;
using ii = pair<int,int>; using lu = unsigned long long; using l = long long;
using vs = vector<string>; using vii = vector<ii>;
using vl = vector<l>; using vvl = vector<vl>; using vvvl = vector<vvl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>; using sl = unordered_set<l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; const double PI = M_PI;
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

void solve(istream& in, ostream& out);
int main(int argc, char **argv) {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  tst::test_init(argc, argv);
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  tst::maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
const l MOD = e9 + 7; // end of template
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

oid sort_suffix_array(vl& sa, vl& rank, l k) {
  l n = sa.size();
  vl counts(max(n + 1, (l)300));
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
    l r = 1;
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

void solve(istream& in, ostream& out) {
  string s; in >> s;
  l n = s.size();
  l k; in >> k;
  auto sa = build_suffix_array(s);
  auto lcp = build_lcp(s, sa);
  F(i, 0, sa.size()) {
    l p = sa[i];
    l x = max(l(0), n - p - lcp[i]);
    if (I(x, k) >= k) {
      I("out", p, lcp[i] + k - 1);
      out << s.substr(p, lcp[i] + k) << lf;
      break;
    }
    k -= x;
  }
}
