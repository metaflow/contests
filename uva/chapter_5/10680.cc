#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 1000001;

vi memo(MAX, 1);

void sieve() {
  bitset<MAX> b;
  b.reset();
  for (ll i = 2; i < b.size(); i++) {
    if (b[i]) continue;
    for (ll j = i * i; j < b.size(); j += i) b.set(j);
    ll t = i;
    while (t < b.size()) {
      memo[t] = i;
      t *= i;
    }
  }
  for (int i = 2; i < MAX; i++) {
    memo[i] *= memo[i - 1];
    if (memo[i] % 10 == 0) memo[i] /= 10;
    memo[i] %= 100;
  }
}

int main() {
  ll n;
  sieve();
  while (cin >> n, n) {
    cout << memo[n] % 10 << endl;
  }
}
