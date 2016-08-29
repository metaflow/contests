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

const string symbol[] = {"I", "V", "X", "L", "C", "D", "M", "&", "#"};
const ll value[] = {1, 5, 10, 50, 100, 500, 1000};
const ll cost[] = {1, 2, 2, 2, 2, 3, 4, 0, 0};

ll to_romain(ll n) {
  ll p = 6;
  ll r = 0;
  while (n) {
    auto i = cost[p];
    auto v = cost[p + 1];
    auto x = cost[p + 2];
    switch (n / value[p]) {
      case 0: break;
      case 1: r += i; break;
      case 2: r += i + i; break;
      case 3: r += i + i + i; break;
      case 4: r += i + v; break;
      case 5: r += v; break;
      case 6: r += v + i; break;
      case 7: r += v + i + i; break;
      case 8: r += v + i + i + i; break;
      case 9: r += i + x; break;
    }
    n -= (n / value[p]) * value[p];
    p -= 2;
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n) {
    cout << to_romain(n) << endl;
  }
}
