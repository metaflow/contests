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
  ll n;
  while (cin >> n) {
    vll v(n);
    bool ok = true;
    for (ll i = 0; i < n; i++) {
      cin >> v[i];
      while (v[i] % 3 == 0) v[i] /= 3;
      while (v[i] % 2 == 0) v[i] /= 2;
      if (v[i] != v[0]) ok = false;
    }
    if (ok) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
}

