// time 14:00
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
const int MAX = 100002;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n) {
    vll v(n);
    for (ll i = 0; i < n; i++) cin >> v[i];
    ll i = 0;
    ll answer = 0;
    while (i < n) {
      ll j = i;
      while (j < n && v[i] == v[j]) j++;
      ll t = (j - i);
      i = j;
      answer += t * (t + 1) / 2;
    }
    cout << answer << endl;
  }
}
