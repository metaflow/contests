#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

vector<long> primes;

void prepare_primes() {
  bitset<50000> b;
  b.reset();
  primes.emplace_back(2);
  for (ll i = 3; i < b.size(); i+= 2) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j < b.size(); j += i) b[j] = true;
  }
}

bool is_prime(ll n) {
  auto p = primes.begin();
  while (p != primes.end() && ((*p) * (*p) <= n)) {
    if (n % (*p) == 0) return false;
    p++;
  }
  return true;
}

int main() {
  prepare_primes();
  bitset<1000010> b;
  ll L, U;
  while (cin >> L >> U) {
    int min_distance = INF; int min_a;
    int max_distance = 0; int max_a;
    int k = 0;

    if (L <= 2) {
      k = 2;
      L = 3;
    }
    if (L % 2 == 0) L++;

    b.reset();
    for (auto p = primes.begin(); p != primes.end() && (*p)*(*p) <= U; p++) {
      ll from = L;
      if (L % (*p) != 0) from = L - L % (*p) + (*p);
      if (from == (*p)) from += *p;
      for (ll j = from; j <= U; j += (*p)) b.set(j - L);
    }

    for (ll i = L; i <= U; i += 2) {
      if (b[i - L]) continue;
      if (k != 0) {
        if (min_distance > i - k) {
          min_distance = i - k;
          min_a = k;
        }
        if (max_distance < i - k) {
          max_distance = i - k;
          max_a = k;
        }
      }
      k = i;
    }

    if (max_distance == 0) {
      printf("There are no adjacent primes.\n");
    } else {
      printf("%d,%d are closest, %d,%d are most distant.\n",
        min_a, min_a + min_distance, max_a, max_a + max_distance);
    }
  }
}
