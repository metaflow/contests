#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <queue>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using vl = vector<ll>;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

vl primes;

void find_primes() {
  bitset<31630000> b;
  b.reset();
  primes.push_back(2);
  for (ll i = 3; i < 5700; i += 2) {
    if (b[i]) continue;
    primes.push_back(i);
    for (ll j = i * i; j < b.size(); j += i) b[j] = true;
  }
  for (ll i = 5701; i < b.size(); i += 2) {
    if (!b[i]) primes.push_back(i);
  }
}

ll lpd(ll n) {
  ll r = -1;
  bool only = true;
  for (auto p : primes) {
    if (p * p > n) break;
    if (n % p == 0) {
      if (!only) r = p;
      only = false;
      while (n % p == 0) n /= p;
    }
  }
  if (n != 1 && !only) r = n;
  return r;
}

int main() {
  find_primes();
  ll n;
  while (cin >> n, n) {
    ll m = lpd(abs(n));
    printf("%lld\n", m);
  }
}
