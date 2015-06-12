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

const int L = 26;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string a, b, c;
  while (cin >> a >> b >> c) {
    if (b.size() < c.size()) swap(b, c);
    vi ca(L), cb(L), cc(L);
    for (auto s : a) ca[s - 'a']++;
    for (auto s : b) cb[s - 'a']++;
    for (auto s : c) cc[s - 'a']++;
    int mb = INF;
    for (ll i = 0; i < L; i++) {
      if (cb[i] == 0) continue;
      mb = min(mb, ca[i] / cb[i]);
    }
    int mc = INF;
    for (ll i = 0; i < L; i++) {
      if (cc[i] == 0) continue;
      mc = min(mc, ca[i] / cc[i]);
    }
    int best = -1;
    int best_b = 0;
    int best_c = 0;
    for (ll i = 0; i <= mb; i++) {
      ll m = mc;
      for (ll j = 0; j < L; j++) {
        if (cb[j] != 0 && cc[j] != 0)
        m = min(m, (ca[j] - i * cb[j]) / cc[j]);
      }
      if (m + i > best) {
        best = m + i;
        best_b = i;
        best_c = m;
      }
    }
    for (ll i = 0; i < best_b; i++) cout << b;
    for (ll i = 0; i < best_c; i++) cout << c;
    for (ll i = 0; i < L; i++) {
      int t = ca[i] - cb[i] * best_b - cc[i] * best_c;
      while (t > 0) {
        cout << (char(i + 'a'));
        t--;
      }
    }
    cout << endl;
  }
}
