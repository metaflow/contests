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

// [from, to)
void merge_sort(vll& v, ll from, ll to, ll& k) {
  ll n = to - from;
  if (n < 2) return;
  ll m = (to + from) / 2;
  merge_sort(v, from, m, k);
  merge_sort(v, m, to, k);
  vll T(n);
  ll a = from;
  ll b = m;
  for (ll i = 0; i < n; i++) {
    if (a == m) { T[i] = v[b]; b++; continue; }
    if (b == to) { T[i] = v[a]; a++; continue; }
    if (v[a] <= v[b]) {
      T[i] = v[a];
      a++;
      continue;
    }
    k += m - a;
    T[i] = v[b];
    b++;
  }
  for (ll i = 0; i < n; i++) v[i + from] = T[i];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n) {
    vll V(n);
    for (ll i = 0; i < n; i++) cin >> V[i];
    ll q = 0;
    merge_sort(V, 0, n, q);
    cout << q << endl;
  }
}
