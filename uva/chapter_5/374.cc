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

ll pow_mod(ll b, ll p, ll m) {
  if (p == 0) return 1 % m;
  if (p % 2 == 0) {
    ll t = pow_mod(b, p / 2, m);
    return (t * t) % m;
  }
  return (pow_mod(b, p - 1, m) * b) % m;
}

int main() {
  ll b, p, m;
  while (cin >> b >> p >> m) {
    cout << pow_mod(b, p, m) << endl;
  }
}
