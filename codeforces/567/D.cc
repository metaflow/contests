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

ll e(ll n, ll a) {
  return (n + 1) / (a + 1);
}

struct intervals_key {
  bool operator() (const ii& a, const ii& b) {
    return a.second <= b.first;
 };
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, k, a;
  while (cin >> n >> k >> a) {
    ll estimation = e(n, a);
    ll m; cin >> m;
    set<ii, intervals_key> s;
    s.emplace(0, n);
    ll answer = -1;
    for (ll i = 0; i < m; i++) {
      ll at; cin >> at;
      if (answer != -1) continue;
      ii interval = *(s.equal_range(make_pair(at - 1, at)).first);
      s.erase(interval);
      estimation -= e(interval.second - interval.first, a);
      if (at - 1 > interval.first) {
        auto p = make_pair(interval.first, at - 1);
        estimation += e(p.second - p.first, a);
        s.emplace(p);
      }
      if (interval.second > a) {
        auto p = make_pair(at, interval.second);
        estimation += e(p.second - p.first, a);
        s.emplace(p);
      }
      if (estimation < k) answer = i + 1;
    }
    cout << answer << endl;
  }
}
