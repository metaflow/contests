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

l get_mask(l n) {
  l result = 0;
  while (n) {
    result = result | (1L << (n % 10));
    n /= 10;
  }
  return result;
}

l find_last(l n) {
  if (n == 0) return 0;
  l result = n;
  l mask = get_mask(result);
  l g = (1L << 10) - 1;
  for (l i = 1; i < 1000; i++) {
    if (mask == g) return result;
    result = n * i;
    mask = mask | get_mask(result);
  }
  assert(false);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc;
  cin >> tcc;
  for (l tt = 1; tt <= tcc; tt++) {
    l n; cin >> n;
    l last = find_last(n);
    cout << "Case #" << tt << ": ";
    if (last == 0) {
      cout << "INSOMNIA" << endl;
    } else {
      cout << last << endl;
    }
  }
}
