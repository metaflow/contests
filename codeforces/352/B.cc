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
const int MAX = 100001;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n) {
    vll last_position(MAX, -1);
    vll period(MAX, 0);
    for (ll i = 0; i < n; i++) {
      ll a; cin >> a;
      if (last_position[a] != -1) {
        ll d = i - last_position[a];
        if (period[a] == d || period[a] == 0) {
          period[a] = d;
        } else {
          period[a] = -1;
        }
      }
      last_position[a] = i;
    }
    vector<pair<ll, ll>> answer;
    for (ll i = 0; i < MAX; i++) {
      if (last_position[i] == -1 || period[i] == -1) continue;
      answer.emplace_back(i, period[i]);
    }
    cout << answer.size() << endl;
    for (auto a : answer) cout << a.first << " " << a.second << endl;
  }
}
