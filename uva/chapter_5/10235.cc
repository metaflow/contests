#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

vector<ll> primes;

void sieve() {
  bitset<2000> b;
  primes.emplace_back(2);
  for (ll i = 3; i < b.size(); i += 2) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j < b.size(); j += i) b.set(j);
  }
}

bool prime(int n) {
  auto p = primes.begin();
  while (p != primes.end() && ((*p)*(*p) <= n)) {
    if (n % *p == 0) return false;
    p++;
  }
  return n != 1;
}

int reverse(int a) {
  int b = 0;
  while (a) {
    b = b * 10 + a % 10;
    a /= 10;
  }
  return b;
}

int main() {
  sieve();
  int n;
  while (cin >> n) {
    if (prime(n)) {
      int r = reverse(n);
      if (n != r && prime(r)) {
        printf("%d is emirp.\n", n);
      } else {
        printf("%d is prime.\n", n);
      }
    } else {
      printf("%d is not prime.\n", n);
    }
  }
}
