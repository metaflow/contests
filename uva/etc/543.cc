#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

vi primes;

void prepare_primes() {
  bitset<1000000> b;
  b.reset();
  for (ll i = 2; i < b.size(); i++) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j < b.size(); j += i) b[j] = true;
  }
}

int main() {
  int n;
  prepare_primes();
  while (cin >> n, n) {
    for (auto i : primes) {
      auto j = lower_bound(primes.begin(), primes.end(), n - i);
      if (*j == n - i) {
        printf("%d = %d + %d\n", n, i, *j);
        break;
      }
    }
  }
}
