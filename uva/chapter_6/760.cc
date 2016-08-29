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

vi build_sa(string &s) {
  vi sa(s.size());
  int i;
  for (i = 0; i < (int)s.size(); ++i) sa[i] = i;
  sort(sa.begin(), sa.end(), [s](const int &a, const int &b) {
    return lexicographical_compare(
        s.cbegin() + a, s.cend(),
        s.cbegin() + b, s.cend());
  });
  return sa;
}

vi find_lcp(vi &sa, string &s) {
  int i;
  vi p(sa.size());
  p[sa[0]] = -1;
  for (i = 1; i < (int)s.size(); ++i) p[sa[i]] = sa[i - 1];
  int w = 0;
  vi plcp(sa.size());
  for (i = 0; i < (int)s.size(); ++i) {
    if (p[i] == -1) { plcp[i] = 0; continue; }
    while (s[i + w] == s[p[i] + w]) ++w;
    plcp[i] = w;
    if (w) --w;
  }
  vi lcp(plcp.size());
  for (i = 0; i < (int)lcp.size(); ++i) lcp[i] = plcp[sa[i]];
  return lcp;
}

int main() {
  string a, b;
  int tc = 0;
  while (getline(cin, a)) {
    getline(cin, b);
    ++tc;
    if (tc != 1) cout << endl;
    string s = a + "$" + b + "#";
    auto sa = build_sa(s);
    auto lcp = find_lcp(sa, s);
    int m = 1;
    vi r;
    for (uint i = 1; i < sa.size(); ++i) {
      if (lcp[i] < m) continue;
      if ((sa[i] < a.size()) ^ (sa[i - 1] < a.size())) {
        if (lcp[i] > m) { r.clear(); m = lcp[i]; }
        r.emplace_back(i);
      }
    }
    if (r.empty()) {
      cout << "No common sequence." << endl;
    } else {
      string latest = "";
      for (auto i : r) {
        string t = s.substr(sa[i], lcp[i]);
        if (t == latest) continue;
        latest = t;
        cout << t << endl;
      }
    }
    getline(cin, s);
  }
}

// time : 57:43 (wa: incorrect input processing and possible duplicates in output)
