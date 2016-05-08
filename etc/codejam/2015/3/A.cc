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

const int MAX = 1000007;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n, D; cin >> n >> D;
    vll S(n), M(n);
    vector<tuple<ll, ll, ll>> R(n); // salary / position
    ll as, cs, rs, am, cm, rm;
    cin >> S[0] >> as >> cs >> rs;
    cin >> M[0] >> am >> cm >> rm;
    get<0>(R[0]) = 0;
    get<1>(R[0]) = S[0];
    get<2>(R[0]) = S[0];
    for (ll i = 1; i < n; i++) {
      S[i] = (S[i - 1] * as + cs) % rs;
      M[i] = (M[i - 1] * am + cm) % rm;
      ll parent = M[i] % i;
      get<0>(R[i]) = i;
      get<1>(R[i]) = max(S[i], get<1>(R[parent]));
      get<2>(R[i]) = min(S[i], get<2>(R[parent]));
    }
    auto L = R;
    sort(R.begin(), R.end(), [&] (const tuple<ll, ll, ll> &a,
      const tuple<ll, ll, ll> &b) {
      if (get<1>(a) != get<1>(b)) return get<1>(a) < get<1>(b);
      return get<0>(a) < get<0>(b);
    });
    sort(L.begin(), L.end(), [&] (const tuple<ll, ll, ll> &a,
      const tuple<ll, ll, ll> &b) {
      if (get<2>(a) != get<2>(b)) return get<2>(a) < get<2>(b);
      return get<0>(a) > get<0>(b);
    });
    ll answer = 0;

    bitset<MAX> works;
    works[0] = true;
    ll w = 1;
    auto l = L.begin();
    auto r = R.begin();
    while (r != R.end() && l != L.end()) {
      while (l != L.end() && (get<1>(*r) - get<2>(*l) > D)) {
        if (works[get<0>(*l)]) {
          works[get<0>(*l)] = false;
          // cout << " - l " << get<0>(*l) << endl;
          w--;
        }
        l++;
      }
      if (l == L.end()) break;
      answer = max(answer, w);
      // cout << answer << endl;
      r++;
      if (!works[get<0>(*r)] && (get<2>(*r) >= get<2>(*l))) {
        works[get<0>(*r)] = true;
        // cout << " + r " << get<0>(*r) << endl;
        w++;
      }
    }

    cout << "Case #" << tc << ": " << answer << endl;
  }
}
