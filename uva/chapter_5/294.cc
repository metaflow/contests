#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ivi = vi::iterator;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

vi primes;

void sieve() {
  bitset<40000> b;
  primes.emplace_back(2);
  for (ll i = 3; i < b.size(); i += 2) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j < b.size(); j += i) b.set(j);
  }
}

int count(int n) {
  int c = 1;
  auto p = primes.begin();
  while (p != primes.end() && n >= (*p) * (*p)) {
    int a = 0;
    while (n % (*p) == 0) {
      a++;
      n /= *p;
    }
    c *= (a + 1);
    p++;
  }
  if (n != 1) c *= 2;
  return c;
}

int main() {
  sieve();
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int f, t;
    cin >> f >> t;
    int best_c = 0;
    int best_i = 0;
    for (int i = f; i <= t; i++) {
      int k = count(i);
      if (k > best_c) {
        best_c = k;
        best_i = i;
      }
    }
    printf("Between %d and %d, %d has a maximum of %d divisors.\n",
      f, t, best_i, best_c);
  }
}
