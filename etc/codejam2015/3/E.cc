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

void add(vvi& m, size_t p, int d) {
  int n = m[0].size();
  for (size_t i = 0; i < m.size(); i++) {
    int k =  p + (1 << i);
    for (ll j = p ; j < k; j++) {
      m[i][j % n] += d;
    }
  }
}

void print_m(vvi& m) {
  for (auto v : m) {
    for (size_t i = 0; i < v.size(); i++) {
      if (i) cout << " ";
      cout << v[i];
    }
    cout << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    cerr << tc << " ";
    int n, d;
    cin >> n >> d;
    vi v(n);
    for (ll i = 0; i < n; i++) { cin >> v[i]; }
    int levels = 0;
    while ((1LL << levels) < d) levels++;
    levels += 2;
    vvi m(levels);
    for (ll i = 0; i < levels ; i++) m[i].resize(2 * d);
    bool cheaters = false;
    for (ll i = 0; i < n; i++) {
      if (i < 2 * d) {
        add(m, i, v[i]);
      } else {
        cheaters = cheaters || (v[i] != v[i % (2 * d)]);
      }
    }
    ll answer = 0;
    while (!cheaters) {
      // print_m(m);
      // cout << "-----" << endl;
      ll eq = 0;
      while (eq < levels) {
        ll bottom = m[eq][0];
        bool ok = true;
        for (ll j = 0; j < 2 * d; j++) {
          if (m[eq][j] != bottom) { ok = false; break; }
        }
        if (ok) break;
        eq++;
      }
      if (eq == levels) {
        cheaters = true;
        break;
      }
      if (eq == 0) break;
      // cout << "eq " << eq << endl;
      int bottom = m[eq - 1][0];
      for (auto i : m[eq - 1]) bottom = min(bottom, i);
      for (ll i = 0; i < 2 * d; i++) {
        ll j = (i + 1) % (2 * d);
        if (m[eq - 1][i] == bottom && m[eq - 1][j] != bottom) {
          answer++;
          int q = (1 << (eq - 1));
          for (ll k = 0; k < 2 * d; k++) {
            if ((k / q) % 2 == 0) add(m, (k + j) % (2 * d), -1);
          }
          break;
        }
      }
    }
    cout << "Case #" << tc << ": ";
    if (cheaters) {
      cout << "CHEATERS!" << endl;
    } else {
      cout << answer << endl;
    }
  }
}
