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

  vll seq;
  ll a = 0; ll b = 1;
  for (int i = 0; i < 100; i++) {
    ll t = b;
    b += a;
    a = t;
    if (b % 2 == 0) seq.emplace_back(b);
    if (b > 40000000000000000) break;
  }

  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n; cin >> n;
    ll answer = 0;
    for (auto i : seq) {
      if (i > n) break;
      answer += i;
    }
    cout << answer << endl;
  }
}
