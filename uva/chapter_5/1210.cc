#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 10001;

vector<ll> sums;
ll memo[MAX];

void sieve() {
  bitset<MAX> b;
  sums.emplace_back(0);
  sums.emplace_back(2);
  for (ll i = 3; i < b.size(); i += 2) {
    if (b[i]) continue;
    sums.emplace_back(sums.back() + i);
    for (ll j = i * i; j < b.size(); j += i) b.set(j);
  }
}

void count() {
  fill_n(memo, MAX, 0);
  for (int i = 0; i < sums.size(); i++) {
    for (int j = i + 1; j < sums.size(); j++) {
      ll t = sums[j] - sums[i];
      if (t >= MAX) break;
      memo[t]++;
    }
  }
}

int main() {
  sieve(); count();
  int n;
  while (cin >> n, n) cout << memo[n] << endl;
}
