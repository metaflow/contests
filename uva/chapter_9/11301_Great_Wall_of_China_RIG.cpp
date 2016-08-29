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

default_random_engine source(random_device{}());

ll random_in_range(ll a, ll b) {
  return uniform_int_distribution<ll>(a, b)(source);
}

bool random_bool() {
  return random_in_range(0, 1) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size() - 1)];
  }
  return s;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll cases = 10;
  for (ll i = 0; i < cases; i++) {
    ll n = random_in_range(3, 1000);
    // if (i == cases - 1) n = 1000;
    vll starts = {0, 1, 2, 3, 4};
    cout << n << endl;
    for (ll j = 0; j < 5; j++) swap(starts[j], starts[random_in_range(j, 4)]);
    for (ll j = 0; j < 5; j++) {
      if (j == starts[0] || j == starts[1] || j == starts[2]) {
        cout << '@';
      } else {
        cout << '0';
      }
      for (ll k = 1; k < n; k++) {
        cout << random_in_range(0, 9);
      }
      cout << endl;
    }
  }
  cout << 0 << endl;
}
