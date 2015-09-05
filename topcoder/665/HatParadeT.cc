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
  set<int> ss;
  for (ll i = 0; i < 10000; i++) {
    ll c = 0;
    ll n = random_in_range(1, 9);
    vi p(n);
    for (ll i = 0; i < n; i++) p[i] = i;
    vll a(n), b(n);
    ll S = 0;
    for (ll i = 0; i < n; i++) {
      a[i] = random_in_range(1, 5);
      S += a[i];
      b[i] = random_in_range(1, 50);
    }
    // for (ll i = 0; i < n; i++) if (random_bool()) b[i] = S - b[i] + a[i];
    while (true) {
      ll P = 0;
      bool ok = true;
      for (ll i = 0; i < n; i++) {
        P += a[p[i]];
        if (P == b[p[i]] || P + b[p[i]] == S + a[p[i]]) continue;
        ok = false;
      }
      P = 0;
      for (ll i = n - 1; i >= 0; i--) {
        P += a[p[i]];
        if (P == b[p[i]] || P + b[p[i]] == S + a[p[i]]) continue;
        ok = false;
      }
      if (ok) c++;
      if (!next_permutation(p.begin(), p.end())) break;
    }
    // if (c == 1) {
    //   for (auto i : a) cout << i << " ";
    //   cout << endl;
    //   for (auto i : b) cout << i << " ";
    //   cout << endl;
    // }
    ss.emplace(c);
  }
  for (auto i : ss) cout << i << endl;
}
