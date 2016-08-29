#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

const int MAXH = 1000001;
const int MAX = MAXH / 4;
int cumulative[MAX + 1];
void sieve() {
  bitset<MAX + 1> b;
  vll primes;
  for (ll i = 1; i <= MAX; i++) {
    if (b[i]) continue;
    ll v = i * 4 + 1;
    primes.emplace_back(v);
    for (ll j = 1; (j * 4 + 1) * v <= MAXH; j++) b[(j * 4 + 1) * v / 4] = true;
  }
  fill_n(cumulative, MAX + 1, 0);
  for (auto a : primes) {
    for (auto b : primes) {
      if (a * b > MAXH) break;
      cumulative[a * b / 4] = 1;
    }
  }
  int c = 0;
  for (int i = 0; i <= MAX; i++) {
    c += cumulative[i];
    cumulative[i] = c;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  sieve();
  int h;
  while (cin >> h, h) {
    cout << h << " " << cumulative[h / 4] << endl;
  }
}
