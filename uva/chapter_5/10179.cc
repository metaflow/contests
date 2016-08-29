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
  bitset<32000> b; // 32000^2 > 10^9
  b.reset();
  primes.push_back(2);
  for (int i = 3; i < b.size(); i += 2) {
    if (b[i]) continue;
    primes.push_back(i);
    for (int j = i * i; j < b.size(); j += i) b[j] = true;
  }
}

vl divisors(ll n) {
  vl d;
  for (auto p : primes) {
    if (p * p > n) break;
    if (n % p == 0) {
      d.push_back(p);
      while (n % p == 0) n /= p;
    }
  }
  if (n != 1) d.push_back(n);
  return d;
}

int main() {
  find_primes();
  ll n;
  while (cin >> n, n) {
    auto d = divisors(n);
    for (auto i : d) {
      n = (n / i) * (i - 1);
    }
    cout << n << endl;
  }
}
