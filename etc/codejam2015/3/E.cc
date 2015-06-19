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

void addv(vvi& m, vi v, vi& bottoms) {
  int n = m[0].size();
  for (size_t i = 0; i < m.size(); i++) {
    auto u = v;
    int k = (1 << i);
    for (ll j = 0; j < n; j++) {
      m[i][j] += v[j];
      bottoms[i] = min(bottoms[i], m[i][j]);
      u[j] += v[(j - k + n) % n];
    }
    swap(u, v);
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
    cerr << tc;
    int n, d;
    cin >> n >> d;
    vi v(2 * d);
    bool cheaters = false;
    for (ll i = 0; i < n; i++) {
      int a; cin >> a;
      if (i < 2 * d) {
        v[i] = a;
      } else {
        cheaters = cheaters || (a != v[i % (2 * d)]);
      }
    }
    int levels = 0;
    while ((1LL << levels) < d) levels++;
    levels += 2;
    vvi m(levels);
    vi bottoms(levels, INF);
    for (ll i = 0; i < levels ; i++) m[i].resize(2 * d);
    addv(m, v, bottoms);
    cerr << ".";
    ll answer = 0;
    while (!cheaters) {
      ll eq = 0;
      while (eq < levels) {
        bool ok = true;
        for (ll j = 0; j < 2 * d; j++) {
          if (m[eq][j] != bottoms[eq]) { ok = false; break; }
        }
        if (ok) break;
        eq++;
      }
      if (eq == levels) {
        cheaters = true;
        break;
      }
      if (eq == 0) break;
      for (ll i = 0; i < 2 * d; i++) {
        ll j = (i + 1) % (2 * d);
        if (m[eq - 1][i] != bottoms[eq - 1] ||
            m[eq - 1][j] == bottoms[eq - 1]) continue;
        answer++;
        int q = (1 << (eq - 1));
        vi v(2 * d);
        for (ll k = 0; k < 2 * d; k++) {
          if ((k / q) % 2 == 0) v[(k + j) % (2 * d)] = -1;
        }
        addv(m, v, bottoms);
        if (bottoms[0] < 0) cheaters = true;
        break;
      }
    }
    // print_m(m);
    cout << "Case #" << tc << ": ";
    if (cheaters) {
      cout << "CHEATERS!" << endl;
    } else {
      cout << answer << endl;
    }
  }
}
