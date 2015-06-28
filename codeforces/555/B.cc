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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, m;
  while (cin >> n >> m) {
    ll x1, y1;
    cin >> x1 >> y1;
    vector<tuple<ll, ll, ll>> ranges;
    for (ll i = 0; i < n - 1; i++) {
      ll x2, y2; cin >> x2 >> y2;
      ranges.emplace_back(y2 - x1, x2 - y1, i);
      x1 = x2;
      y1 = y2;
    }
    set<pair<ll, ll>> bridges;
    for (ll i = 0; i < m; i++) {
      pair<ll, ll> bridge;
      cin >> bridge.first;
      bridge.second = i + 1;
      bridges.insert(bridge);
    }
    sort(ranges.begin(), ranges.end());
    auto r = ranges.begin();
    vi assign(ranges.size());
    bool ok = true;
    while (r != ranges.end()) {
      pair<ll, ll> probe(get<1>(*r), 0);
      auto b = bridges.lower_bound(probe);
      if (b == bridges.end() || b->first > get<0>(*r)) { ok = false; break; }
      assign[get<2>(*r)] = b->second;
      bridges.erase(b);
      r++;
    }
    if (ok) {
      cout << "Yes" << endl;
      for (ll i = 0; i < n - 1; i++) {
        if (i) cout << " ";
        cout << assign[i];
      }
      cout << endl;
    } else {
      cout << "No" << endl;
    }
  }
}
