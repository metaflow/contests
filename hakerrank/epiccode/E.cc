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
  ll n; cin >> n;
  vii segments(n);
  for (ll i = 0; i < n; i++) cin >> segments[i].first >> segments[i].second;
  vi c(n);
  auto cmp = [] (const ii& a, const ii& b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second > b.second;
  };
  sort(segments.begin(), segments.end(), cmp);
  vi lis;
  for (auto s : segments) {
    auto l = lower_bound(lis.begin(), lis.end(), s.second);
    if (l == lis.end()) {
      lis.emplace_back(s.second);
    } else {
      *l = s.second;
    }
  }
  cout << lis.size() << endl;
}
