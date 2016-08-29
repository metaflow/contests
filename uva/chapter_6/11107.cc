#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <queue>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;
using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

void csort(vi &ra, vi &sa, size_t sh) {
  vi c(max(255, (int)ra.size()));
  size_t i;
  for (i = 0; i < ra.size(); ++i) {
    int t = 0;
    if (sa[i] + sh < ra.size()) t = ra[sa[i] + sh];
    ++c[t];
  }

  int s = 0;
  for (i = 0; i < c.size(); ++i) {
    int t = c[i];
    c[i] = s;
    s += t;
  }

  vi sa_(sa.size());
  for (i = 0; i < sa.size(); ++i) {
    int t = 0;
    if (sa[i] + sh < ra.size()) t = ra[sa[i] + sh];
    sa_[c[t]++] = sa[i];
  }

  sa_.swap(sa);
}

vi build_sa(string &s) {
  size_t i, j;
  vi sa(s.size());
  vi ra(s.size());
  for (i = 0; i < s.size(); ++i) {
    sa[i] = i;
    ra[sa[i]] = s[i];
  }

  vi ra_(ra.size());
  for (i = 1; i < s.size(); i <<= 1) {
    csort(ra, sa, i);
    csort(ra, sa, 0);
    int t = 0;
    ra_[sa[0]] = 0;
    for (j = 1; j < ra.size(); ++j) {
      if (ra[sa[j]] == ra[sa[j - 1]] &&
          ra[sa[j] + i] == ra[sa[j - 1] + i]) --t;
      ra_[sa[j]] = ++t;
    }
    ra_.swap(ra);
    if (ra.back() == (int)ra.size() - 1) break;
  }

  return sa;
}

vi build_lcp(vi &sa, string &s) {
  size_t i;
  vi lcp(sa.size()), plcp(sa.size());

  vi p(sa.size());
  p[sa[0]] = -1;
  for (i = 1; i < sa.size(); ++i) p[sa[i]] = sa[i - 1];
  int l = 0;
  for (i = 0; i < sa.size(); ++i) {
    if (p[i] == -1) { plcp[i] = 0; continue; }
    while (s[i + l] == s[p[i] + l] && s[i + l] != '$') ++l;
    plcp[i] = l;
    if (l) --l;
  }
  for (i = 0; i < sa.size(); ++i) {
    lcp[i] = plcp[sa[i]];
  }
  return lcp;
}

vi mark(vector<string> &dna, vi &sa) {
  size_t i;
  vi m(sa.size());
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

vi collect(vi &sa, vi &lcp, vi &m, int w, int h) {
  vi r;
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

vi find_matches(vi &sa, vi &lcp, vi &m, int h, int &l) {
  vi r;
  int u = 0;
  for (auto i : lcp) u = max(u, i + 1);
  l = 1;

  // upper_bound
  while (l != u) {
    int t = l + (u - l) / 2;
    r = collect(sa, lcp, m, t, h);
    if (r.empty()) {
      u = t;
    } else {
      l = t + 1;
    }
  }

  --l;
  if (l != 0) r = collect(sa, lcp, m, l, h);

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
      auto sa = build_sa(s);
      auto lcp = build_lcp(sa, s);
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
