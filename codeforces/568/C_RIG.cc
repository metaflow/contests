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

double random_double(double a, double b) {
  return uniform_real_distribution<double>(a, b)(source);
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
  ll n = random_in_range(1, 9);
  double density = random_double(0, 1);
  ll q = random_in_range(1, 9);
  for (ll i = 0; i < q; i++) cout << (random_bool() ? 'V' : 'C');
  cout << endl;
  vector<tuple<int, char, int, char>> rules;
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < n; j++) {
      if (j == i) continue;
      if (random_double(0, 1) > density) continue;
      rules.emplace_back(i, (random_bool() ? 'V' : 'C'), j, (random_bool() ? 'V' : 'C'));
    }
  }
  cout << n << " " << rules.size() << endl;
  for (auto r : rules) {
    cout << get<0>(r) + 1 << " " << get<1>(r) << " "
         << get<2>(r) + 1 << " " << get<3>(r) << endl;
  }
  for (ll i = 0; i < n; i++) cout << (char)('a' + random_in_range(0, q - 1));
  cout << endl;
}
