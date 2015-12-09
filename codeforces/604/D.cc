#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

// (base^power) % mod, safe for l near max
l pow_mod(l base, l power, l mod) {
  l r = 1;
  while (power) {
    if (power % 2) r = (r * base) % mod;
    base = (base * base) % mod;
    power /= 2;
  }
  return r;
}

const l MOD = e9 + 7;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l p, k;
  while (cin >> p >> k) {
    if (k == 0) {
      cout << pow_mod(p, p - 1, MOD) << endl;
      continue;
    }
    if (k == 1) {
      cout << pow_mod(p, p, MOD) << endl;
      continue;
    }
    vector<bool> bs(p);
    l pow = 0;
    for (l i = 1; i < p; i++) {
      if (bs[i]) continue;
      l j = i;
      l w = 0;
      while (!bs[j]) {
        w++;
        bs[j] = true;
        j = (j * k) % p;
      }
      // if (pow_mod(k, w, p) == 1) pow++;
      pow++;
    }
    cout << pow_mod(p, pow, MOD) << endl;
  }
}
