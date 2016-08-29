#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 33000;
vi primes;

void sieve() {
  bitset<MAX> b;
  primes.emplace_back(2);
  for (ll i = 3; i < b.size(); i += 2) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j < b.size(); j += i) b.set(j);
  }
}

ll as_number(vector<ii> &p) {
  ll a = 1;
  for (auto i = p.begin(); i != p.end(); i++) {
    a *= pow(i->first, i->second);
  }
  return a;
}

vector<ii> as_primes(ll n) {
  auto p = primes.begin();
  vector<ii> r;
  while (p != primes.end() && (*p)*(*p) <= n) {
    int c = 0;
    while (n % (*p) == 0) {
      c++;
      n /= *p;
    }
    if (c) r.emplace_back(*p, c);
    p++;
  }
  if (n != 1) r.emplace_back(n, 1);
  return r;
}

int main() {
  sieve();
  string s;
  while (getline(cin, s), s != "0") {
    int n, e;
    stringstream ss(s);
    vector<ii> r;
    while (ss >> n >> e) {
      r.emplace_back(n, e);
    }
    ll a = as_number(r);
    r = as_primes(a - 1);
    auto p = r.rbegin();
    while (true) {
      printf("%d %d", p->first, p->second);
      p++;
      if (p == r.rend()) break;
      printf(" ");
    }
    printf("\n");
  }
}
