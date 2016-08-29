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

const ll MOD = 10000000000000007;
const int G = 20;

vi to_v(ll n) {
  vi d(G);
  int i = 0;
  while (n) {
    d[i] = n % 100;
    n /= 100;
    i++;
  }
  return d;
}

vi mult_mod(const vi a, const vi b) {
  vi c(G);
  for (int i = 0; i < G / 2; i++) {
    for (ll j = 0; j < G / 2; j++) {
      c[i + j] += a[i] * b[j];
    }
  }
  ll r = 0;
  for (int i = G - 1; i >= 0; i--) {
    // r = () % MOD;
    r = (r * 100 + c[i]) % MOD;
  }
  return to_v(r);
}

vi power(vi base, const ll p) {
  if (p == 1) return base;
  auto t = power(base, p / 2);
  auto a = mult_mod(t, t);
  if (p % 2 == 1) a = mult_mod(a, base);
  return a;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll r, c;
    cin >> r >> c;
    ll p = (r * c) / 2;
    ll q = r * c - p;
    auto answer = power(to_v(p), q - 1);
    answer = mult_mod(answer, power(to_v(q), p - 1));
    int i = G - 1;
    while (i > 0 && answer[i] == 0) i--;
    while (i >= 0) {
      cout << answer[i] << setw(2) << setfill('0');
      i--;
    }
    cout << setw(0);
    cout << endl;
  }
}
