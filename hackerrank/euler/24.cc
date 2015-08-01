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

const int MAX = 13;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);\
  vll f(MAX);
  f[0] = 1;
  for (ll i = 1; i < MAX; i++) f[i] = f[i - 1] * i;
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    vb used(MAX);
    vll permutation;
    ll n; cin >> n; n--;
    for (int i = 0; i < MAX; i++) {
      ll p = n / f[MAX - 1 - i];
      n -= p * f[MAX - 1 - i];
      for (int j = 0; j < MAX; j++) {
        if (used[j]) continue;
        if (p == 0) {
          permutation.emplace_back(j);
          used[j] = true;
          break;
        }
        p--;
      }
    }
    for (auto i : permutation) cout << char('a' + i);
    cout << endl;
  }
}
