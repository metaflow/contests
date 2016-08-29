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

string inversion_index(string s, ll& n) {
  if (s.size() == 1) {
    return s;
  }
  auto a = inversion_index(s.substr(0, s.size() / 2), n);
  auto b = inversion_index(s.substr(s.size() / 2), n);
  string c;
  auto ia = a.begin();
  auto ib = b.begin();
  for (ll i = 0; i < ll(s.size()); i++) {
    if (ia == a.end()) {
      c += *ib;
      ib++;
      continue;
    }
    if (ib == b.end()) {
      c += *ia;
      ia++;
      continue;
    }
    if (*ia <= *ib) {
      c += *ia;
      ia++;
      continue;
    }
    n += a.end() - ia;
    c += *ib;
    ib++;
  }
  return c;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    if (tc != 1) cout << endl;
    ll n, t; cin >> t >> n;
    vector<tuple<ll, ll, string>> E;
    for (ll i = 0; i < n; i++) {
      string s;
      cin >> s;
      ll q = 0;
      inversion_index(s, q);
      E.emplace_back(q, i, s);
    }
    sort(E.begin(), E.end());
    for (auto e : E) {
      cout << get<2>(e) << endl;
    }
  }
}
