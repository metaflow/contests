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
const int MAX = 100001;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vll c(MAX);
  vll abundant;
  for (int i = 1; i < MAX; i++) {
    if (c[i] > i) abundant.emplace_back(i);
    ll j = i * 2;
    while (j < MAX) {
      c[j] += i;
      j += i;
    }
  }
  bitset<MAX> f;
  for (auto i : abundant) {
    for (auto j : abundant) {
      if (i + j < MAX) f[i + j] = true;
    }
  }
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n; cin >> n;
    if (f[n]) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
