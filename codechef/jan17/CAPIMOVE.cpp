#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>

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

#define _ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc;
  cin >> tcc;
  while (tcc--) {
    LOG << "-------" << endl;
    l n;
    cin >> n;
    vll w(n);
    for (l i = 0; i < n; i++) {
      cin >> w[i].first;
      w[i].second = i;
    }
    sort(w.begin(), w.end(), greater<ll>());
    for (auto d : w) {
      LOG << d.first << " " << d.second << endl;
    }
    LOG << endl;
    vl back_index(n);
    vvl r(n);
    for (l i = 0; i < n; i++) {
      back_index[w[i].second] = i;
      r[i].emplace_back(i);
    }
    for (l i = 0; i < n - 1; i++) {
      l a, b; cin >> a >> b;
      a = back_index[a - 1];
      b = back_index[b - 1];
      r[a].emplace_back(b);
      r[b].emplace_back(a);
    }
    for (auto& t : r) {
      sort(t.begin(), t.end());
    }
    for (l i = 0; i < n; i++) {
      if (i) cout << ' ';
      l j = back_index[i];
      if (r[j].size() == n) {
        cout << 0;
        continue;
      }
      l a = r[j].size();
      for (auto l : r[j]) {
        LOG << l << " ";
      }
      LOG << endl;
      for (l k = 0; k < r[j].size(); k++) {
        if (r[j][k] != k) {
          a = k;
          break;
        }
      }
      cout << (w[a].second + 1);
    }
    cout << endl;
  }
}
