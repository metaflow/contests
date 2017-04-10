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
const l e0=1, e3=1000, e5=100000, e6=e3*e3, e7=10*e6, e8=10*e7, e9=10*e8;
#define ALL(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

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

vl build_suffix_array(string s) {
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
    while (s[i + w] == s[p[i] + w] && s[i + w] != '$') w++;
    plcp[i] = w;
    if (w) --w;
  }
  F(i, 0, n) lcp[i] = plcp[sa[i]];
  return lcp;
}

vl mark(vector<string> &dna, vl &sa) {
  size_t i;
  vl m(sa.size());
  for (i = 0; i < sa.size(); ++i) {
    int v = sa[i];
    m[i] = 0;
    while (v > (int)dna[m[i]].size()) {
      v -= dna[m[i]].size() + 1;
      m[i]++;
    }
  }
  return m;
}

vl collect(vl &sa, vl &lcp, vl &m, l w, l h) {
  vl r;
  bitset<100> b;
  size_t i;
  for (i = 1; i < lcp.size(); ++i) {
    if (lcp[i] < w) {
      b.reset();
      continue;
    }
    b[m[i]] = true;
    b[m[i - 1]] = true;
    if ((int)b.count() == h) r.emplace_back(sa[i]);
  }
  return r;
}

vl find_matches(vl &sa, vl &lcp, vl &m, int h, int &w) {
  vl r;
  l u = 0;
  for (auto i : lcp) u = max(u, i + 1);
  w = 1;

  // upper_bound
  while (w != u) {
    l t = w + (u - w) / 2;
    r = collect(sa, lcp, m, t, h);
    if (r.empty()) {
      u = t;
    } else {
      w = t + 1;
    }
  }

  --w;
  if (w != 0) r = collect(sa, lcp, m, w, h);

  return r;
}

int main() {
  int n;
  int tc = 0;
  while (cin >> n, n) {
    ++tc;
    if (tc != 1) cout << endl;
    vector<string> dna(n);
    string s = "";
    for (size_t i = 0; i < dna.size(); ++i) {
      cin >> dna[i];
      s += dna[i] + "$";
    }

    if (n == 1) {
      cout << dna[0] << endl;
    } else {
      auto sa = build_suffix_array(s);
      auto lcp = build_lcp(s, sa);
      auto m = mark(dna, sa);

      int w;
      auto r = find_matches(sa, lcp, m, n / 2 + 1, w);
      if (r.empty()) {
        cout << "?" << endl;
      } else {
        string last = "";
        for (auto i : r) {
          string t = s.substr(i, w);
          if (t == last) continue;
          last = t;
          cout << t << endl;
        }
      }
    }
  }
}

// time : 2:11:00 started with wrong implementation first (~10 min)
