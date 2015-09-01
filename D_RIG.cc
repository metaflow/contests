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
  ll n = random_in_range(2, 5);
  ll q = 10;
  cout << n << " " << q << endl;
  for (ll j = 0; j < 2; j++) {
    for (ll i = 0; i < n; i++) {
      cout << random_in_range(1, 100) << " ";
    }
    cout << endl;
  }
  ll i = 0;
  while (i < q) {
    ll a = random_in_range(1, n);
    ll b = random_in_range(1, n);
    if (a == b) continue;
    cout << a << " " << b << endl;
    i++;
  }
}
