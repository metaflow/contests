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

bool palindromic(ll a, ll base) {
  vll v;
  while (a) {
    v.emplace_back(a % base);
    a /= base;
  }
  for (ll i = 0; i < v.size() / 2; i++) {
    if (v[i] != v[v.size() - i - 1]) return false;
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, k;
  cin >> n >> k;
  ll answer = 0;
  for (ll i = 1; i < n; i++) {
    if (palindromic(i, 10) && palindromic(i, k)) answer += i;
  }
  cout << answer << endl;
}
