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

const l MOD = e9 * 10;

l mult(l a, l b) {
  l ta = (a / e9) % 10;
  l tb = (b / e9) % 10;
  a %= e9;
  b %= e9;
  return ((a * b) + (((ta * b) + (tb * a)) % 10) * e9) % MOD;
}

l pow_mod(l base, l power) {
  l result = 1;
  while (power) {
    if (power % 2) result = mult(result, base);
    power /= 2;
    base = mult(base, base);
  }
  return result;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  cin >> n;
  l answer = 0;
  for (l i = 1; i <= n; i++) {
    answer = (answer + pow_mod(i, i)) % MOD;
  }
  cout << answer << endl;
}
