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
  for (l i = 0; i < n; i++) {
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
  for (l i = 0; i < n; i++) {
    rank[i] = s[i];
    sa[i] = i;
  }
  for (l k = 1; k < n; k = k << 1) {
    sort_suffix_array(sa, rank, k);
    sort_suffix_array(sa, rank, 0);
    vl updated_rank(rank.size());
    l r = 0;
    updated_rank[sa[0]] = r;
    for (l i = 1; i < n; i++) {
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
  size_t i;
  vl lcp(sa.size()), plcp(sa.size());

  vl p(sa.size());
  p[sa[0]] = -1;
  for (i = 1; i < sa.size(); ++i) p[sa[i]] = sa[i - 1];
  l w = 0;
  for (i = 0; i < sa.size(); ++i) {
    if (p[i] == -1) { plcp[i] = 0; continue; }
    while (s[i + w] == s[p[i] + w] && i + w + 1 < sa.size()) w++;
    plcp[i] = w;
    if (w) --w;
  }
  for (i = 0; i < sa.size(); ++i) {
    lcp[i] = plcp[sa[i]];
  }
  return lcp;
}

vector<string> brute(string s) {
  vector<string> V;
  l n = s.size();
  for (l i = 0; i < n; i++) {
    for (l j = i; j < n; j++) {
      V.emplace_back(s.substr(i, j - i + 1));
    }
  }
  sort(V.begin(), V.end());
  return V;
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

string solve_brute(vector<string>& v, l k) {
  return (k <= v.size()) ? v[k - 1] : "No such line.";
}

string solve(vl& sa, vl& lcp, string& s, l k) {
  l n = s.size() - 1;
  for (l i = 0; i < s.size(); i++) {
    l w = n - sa[i];
    stack<l> st;
    st.push(w);
    l sum = w;
    for (l j = i + 1; j < s.size(); j++) {
      w = min(lcp[j], w);
      if (w == 0) break;
      sum += w;
      st.push(w);
    }
    if (sum >= k) {
      while (st.top() * st.size() < k) { k -= st.top(); st.pop(); }
      l t = k / st.size();
      if (k % st.size()) t++;
      return s.substr(sa[i], t);
    }
    k -= n - sa[i];
  }
  return "No such line.";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  /*
  for (l tc = 0; tc < 100; tc++) {
    string s = random_string(random_in_range(1, 10));
    auto b = brute(s);
    s += '@';
    auto sa = build_suffix_array(s);
    auto lcp = build_lcp(s, sa);
    l p = 0;
    for (l i = 0; i < s.size(); i++) {
      for (l j = i; j < s.size(); j++) {
        p++;
        if (solve_brute(b, p) != solve(sa, lcp, s, p)) {
          cout << s << ' ' << p << '\n';
          cout << solve_brute(b, p) << '\n';
          cout << solve(sa, lcp, s, p) << '\n';
          cout << '\n';
          for (auto a : b) cout << a << '\n';
          cout << '\n';
          for (auto i : sa) cout << s.substr(i) << '\n';
          return 1;
        }
      }
    }
  }
  return 0;
  */
  string s;
  while (cin >> s) {
    s += '@';
    l k; cin >> k;
    auto sa = build_suffix_array(s);
    auto lcp = build_lcp(s, sa);
    cout << solve(sa, lcp, s, k) << '\n';
  }
}
