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

const int MAX = 1000001;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n) {
    ll m = 0, c = 0;
    bitset<MAX> b;
    for (ll i = 0; i < n; i++) {
      char op; ll k;
      cin >> op >> k;
      if (op == '+') {
        b.set(k);
        c++;
        m = max(m, c);
      } else {
        if (b[k]) {
          c--;
        } else {
          m++;
        }
        b[k] = false;
      }
    }
    cout << m << endl;
  }
}
