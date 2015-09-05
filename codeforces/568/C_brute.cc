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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s;
  while (cin >> s) {
    int k = s.size();
    vb types(k);
    for (ll i = 0; i < k; i++) {
      types[i] = (s[i] == 'V');
    }
    vector<tuple<int, bool, int, bool>> rules;
    ll n, m; cin >> n >> m;
    for (ll i = 0; i < m; i++) {
      int a, b; char at, bt;
      cin >> a >> at >> b >> bt;
      a--; b--;
      rules.emplace_back(a, at == 'V', b, bt == 'V');
    }
    cin >> s;
    vi values(n);
    for (ll i = 0; i < n; i++) values[i] = s[i] - 'a';
    while (true) {
      bool ok = true;
      for (auto r : rules) {
        if (types[values[get<0>(r)]] != get<1>(r)) continue;
        if (types[values[get<2>(r)]] == get<3>(r)) continue;
        ok = false;
      }
      if (ok) break;
      values[n - 1]++;
      ll i = n - 1;
      while (i > 0 && values[i] >= k) {
        values[i] = 0;
        i--;
        values[i]++;
      }
      if (values[0] >= k) break;
    }
    if (values[0] >= k) {
      cout << -1 << endl;
    } else {
      for (ll i = 0; i < n; i++) cout << (char)('a' + values[i]);
      cout << endl;
    }
  }
}
