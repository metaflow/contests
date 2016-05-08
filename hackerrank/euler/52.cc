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

vl mask(l x) {
  vl m;
  while (x) {
    m.emplace_back(x % 10);
    x /= 10;
  }
  sort(m.begin(), m.end());
  return m;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l N, K;
  while (cin >> N >> K) {
    for (l x = 1; x <= N; x++) {
      auto t = mask(x);
      bool ok = true;
      for (l m = 2; m <= K; m++) {
        auto u = mask(x * m);
        ok = (u.size() == t.size()) && equal(t.begin(), t.end(), u.begin());
        if (!ok) break;
      }
      if (ok) {
        for (l m = 1; m <= K; m++) {
          if (m != 1) cout << " ";
          cout << (x * m);
        }
        cout << endl;
      }
    }
  }
}
