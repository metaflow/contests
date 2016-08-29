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
const int INF = numeric_limits<int>::max();

vector<ll> primes;

void find_primes() {
  bitset<20000000> b;
  b.reset();
  primes.push_back(2);
  for (ll i = 3; i < b.size(); i += 2) {
    if (b[i]) continue;
    primes.push_back(i);
    for (ll j = i * i; j < b.size(); j += i) b[j] = true;
  }
}

vector<ll> twins;

void find_twins() {
  for (int i = 0; i + 1 < primes.size(); ++i) {
    if (primes[i + 1] - primes[i] == 2) twins.push_back(primes[i]);
  }
}

int main() {
  find_primes();
  cerr << primes.size() << endl;
  find_twins();
  int n;
  while (cin >> n) printf("(%lld, %lld)\n", twins[n - 1], twins[n - 1] + 2);
}
