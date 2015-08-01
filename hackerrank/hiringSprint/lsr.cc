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

void sort_suffix_array(vi& sa, vll& rank, int k) {
  int n = sa.size();
  vi counts(max(n, 300));
  for (int i = 0; i < n; i++) {
    int p = 0;
    if (i + k < n) p = rank[i + k];
    counts[p]++;
  }
  int s = 0;
  for (size_t i = 0; i < counts.size(); i++) {
    int t = counts[i];
    counts[i] = s;
    s += t;
  }
  vi updated_sa(n);
  for (auto i : sa) {
    int p = 0;
    if (i + k < n) p = rank[i + k];
    updated_sa[counts[p]] = i;
    counts[p]++;
  }
  swap(sa, updated_sa);
}

vi build_suffix_array(string s) {
  size_t n = s.size();
  vi sa(n);
  vll rank(n);
  for (size_t i = 0; i < n; i++) {
    rank[i] = s[i];
    sa[i] = i;
  }
  for (size_t k = 1; k < n; k = k << 1) {
    sort_suffix_array(sa, rank, k);
    sort_suffix_array(sa, rank, 0);
    vll updated_rank(rank.size());
    int r = 0;
    updated_rank[sa[0]] = r;
    for (size_t i = 1; i < n; i++) {
      if (rank[sa[i]] != rank[sa[i - 1]] ||
          rank[sa[i] + k] != rank[sa[i - 1] +k]) r++;
      updated_rank[sa[i]] = r;
    }
    swap(rank, updated_rank);
    if (rank[sa[n - 1]] == int(n - 1)) break;
  }
  return sa;
}

vi build_lcp(string &s, vi &sa) {
  size_t i;
  vi lcp(sa.size()), plcp(sa.size());

  vi p(sa.size());
  p[sa[0]] = -1;
  for (i = 1; i < sa.size(); ++i) p[sa[i]] = sa[i - 1];
  int l = 0;
  for (i = 0; i < sa.size(); ++i) {
    if (p[i] == -1) { plcp[i] = 0; continue; }
    while (s[i + l] == s[p[i] + l] && i + l + 1 < sa.size()) ++l;
    plcp[i] = l;
    if (l) --l;
  }
  for (i = 0; i < sa.size(); ++i) {
    lcp[i] = plcp[sa[i]];
  }
  return lcp;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s;
  getline(cin, s);
  string r = s;
  reverse(r.begin(), r.end());
  int n = s.size();
  s = s + '!' + r;
  auto sa = build_suffix_array(s);
  auto lcp = build_lcp(s, sa);
  int best = 0;
  for (size_t i = 0; i < sa.size(); i++) {
    int v = sa[i];
    if (v >= n) v = n - 1 - (v - n - 1);
    // cout << sa[i] << " " << v << " " << lcp[i] <<  " " << s.substr(sa[i]) << endl;
    int p = INF;
    for (size_t j = i + 1; j < sa.size(); j++) {
      p = min(p, lcp[j]);
      if (p == 0 || p <= best) break;
      if ((sa[j] < n) == (sa[i] < n)) continue;
      int u = sa[j];
      if (u >= n) u = n - 1 - (u - n - 1);
      if (sa[j] < n) swap(u, v);
      if (u < v) {
        best = max(best, p);
      } else {
        best = max(best, min(p, (u - v + 1) / 2));
      }
    }
  }
  cout << best << endl;
}
