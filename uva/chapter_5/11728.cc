#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using ivi = vi::iterator;
using ivii = vii::iterator;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 1001;

vi primes;
int memo[MAX];

void sieve() {
  bitset<MAX> b;
  primes.emplace_back(2);
  for (int i = 3; i < b.size(); i += 2) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (int j = i * i; j < b.size(); j +=i) b.set(j);
  }
}

int f(int n, ivi p) {
  if (n == 1) return 1;
  int b = -1;
  while (p != primes.end()) {
    int k = 1;
    int s = 1;
    while (true) {
      k *= *p;
      s += k;
      if (s > n) break;
      if (n % s == 0) {
        int t = f(n / s, p + 1);
        if (t > 0) b = max(b, t * k);
      }
    }
    p++;
  }
  return b;
}

int find(int n) {
  if (memo[n] == -2) {
    memo[n] = f(n, primes.begin());
  }
  return memo[n];
}

int main() {
  sieve();
  fill(&memo[0], &memo[MAX], -2);
  int n;
  int tc = 1;
  while (cin >> n, n) {
    printf("Case %d: %d\n", tc, find(n));
    tc++;
    // break;
  }
}
