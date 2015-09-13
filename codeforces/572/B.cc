// time: 15:00
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
  ll n, s;
  while (cin >> n >> s) {
    map<ll, ll, greater<ll>> buy, sell;
    for (ll i = 0; i < n; i++) {
      char d; ll p, q;
      cin >> d >> p >> q;
      if (d == 'B') {
        buy[p] += q;
      } else {
        sell[p] += q;
      }
    }
    ll i = 0;
    auto it = sell.begin();
    if (s < sell.size()) {
      for (ll j = 0; j < sell.size() - s; j++) {
        it++;
      }
    }
    while (i < s && it != sell.end()) {
      cout << "S " << it->first << " " << it->second << endl;
      it++;
      i++;
    }
    it = buy.begin();
    i = 0;
    while (i < s && it != buy.end()) {
      cout << "B " << it->first << " " << it->second << endl;
      it++;
      i++;
    }
  }
}
