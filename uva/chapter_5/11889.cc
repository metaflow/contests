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
using llu = unsigned long long;
using ui = unsigned int;
const int INF = numeric_limits<int>::max();

vi primes;

void find_primes() {
  bitset<3200> b;
  b.reset();
  primes.push_back(2);
  for (ui i = 3; i < b.size(); i += 2) {
    if (b[i]) continue;
    primes.push_back(i);
    for (ui j = i * i; j < b.size(); j += i) b[j] = true;
  }
}

vector<ii> divisors(int n) {
  vector<ii> r;
  for (ui i = 0; i < primes.size(); ++i) {
    int p = primes[i];
    if (p * p > n) break;
    int c = 0;
    while (n % p == 0) {
      ++c;
      n /= p;
    }
    if (c) {
      r.push_back(ii(p, c));
    }
  }
  if (n != 1) r.push_back(ii(n, 1));
  return r;
}

int get_b(int a, int c) {
  auto da = divisors(a);
  auto dc = divisors(c);
  vector<ii> db;
  auto ia = da.begin();
  auto ic = dc.begin();
  while (ia != da.end() && ic != dc.end()) {
    if (ia->first == ic->first) {
      if (ia->second > ic->second) {
        break;
      }
      if (ia->second < ic->second) {
        db.push_back(*ic);
      }
      ++ia;
      ++ic;
      continue;
    }
    if (ia->first < ic->first) {
      ++ia;
      continue;
    }
    db.push_back(*ic++);
  }

  while (ic != dc.end()) db.push_back(*ic++);

  int b = 1;
  for (auto d : db) {
   for (int i = 0; i < d.second; ++i) b *= d.first;
  }
  return b;
}

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

int main() {
  find_primes();
  int tcc;
  cin >> tcc;
  while (tcc--) {
    ll a, c;
    cin >> a >> c;
    int b = get_b(a, c);
    if (a * b / gcd(a, b) == c) {
      printf("%d\n", b);
    } else {
      printf("NO SOLUTION\n");
    }
  }
}
