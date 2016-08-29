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

string L = "IVXLCDM";
ll V[] = {1, 5, 10, 50, 100, 500, 1000};

string to_romain(ll n) {
  string romain = "";
  ll p = 6;
  while (true) {
    while (n >= V[p]) {
      romain += L[p];
      n -= V[p];
    }
    if (p == 0) break;
    p -= 2;
    ll t = n / V[p];
    if (t < 4) continue;
    n -= t * V[p];
    switch (t) {
      case 4: romain.push_back(L[p]);
              romain.push_back(L[p + 1]);
              break;
      case 5: romain.push_back(L[p + 1]); break;
      case 6: romain.push_back(L[p + 1]);
              romain.push_back(L[p]);
              break;
      case 7: romain.push_back(L[p + 1]);
              romain.push_back(L[p]);
              romain.push_back(L[p]);
              break;
      case 8: romain.push_back(L[p + 1]);
              romain.push_back(L[p]);
              romain.push_back(L[p]);
              romain.push_back(L[p]);
              break;
      case 9: romain.push_back(L[p]);
              romain.push_back(L[p + 2]);
              break;
    }
  }
  return romain;
}

ll to_decimal(string s) {
  ll m = -1;
  ll v = 0;
  for (int i = s.size() - 1; i >= 0; i--) {
    auto c = s[i];
    ll p = L.find(c);
    if (p < m) {
      v -= V[p];
    } else {
      v += V[p];
    }
    m = max(m, p);
  }
  return v;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s;
  while (cin >> s) {
    if (s[0] >= '0' && s[0] <= '9') {
      stringstream ss(s);
      ll n; ss >> n;
      cout << to_romain(n) << endl;
    } else {
      cout << to_decimal(s) << endl;
    }
  }
}
