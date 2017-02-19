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
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

vl kmp_build_back(const string& p) {
  vl b(p.size());
  l j = -1;
  for (size_t i = 0; i < p.size(); i++) {
    b[i] = j;
    while ((j > -1) and (p[j] != p[i])) j = b[j];
    j++;
  }
  return b;
}

bool kmp_search(const string& p, const string& s, const vl& b, function<bool(l,l)> f) {
  l j = 0;
  for (size_t i = 0; i < s.size(); i++) {
    while ((j > -1) and (p[j] != s[i])) j = b[j];
    j++;
    if (f(i, j)) return true;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s;
  while (cin >> s) {
    string rs = s; reverse(rs.begin(), rs.end());
    l s_size = s.size();
    l answer = 0;
    l tcc; cin >> tcc;
    while (tcc--) {
      string p; cin >> p;
      l p_size = p.size();
      if (p_size < 2) continue;
      vl match_length(s.size());
      auto b = kmp_build_back(p);
      if (kmp_search(p, s, b, [&](l at, l m) {
            match_length[at] = max(m, (at > 0) ? match_length[at - 1] : m);
            return m == p_size;
          })) {
        answer++;
        continue;
      }
      reverse(p.begin(), p.end());
      b = kmp_build_back(p);
      if (kmp_search(p, rs, b, [&](l at, l m) {
            return ((s_size - at - 2 >= 0) and
                    (match_length[s_size - at - 2] + m >= p_size));
          })) answer++;
    }
    cout << answer << '\n';
  }
  return 0;
}
