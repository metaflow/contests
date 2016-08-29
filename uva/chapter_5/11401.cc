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

const int MAX = 1000001;

int main() {
  llu tmemo[MAX];
  tmemo[3] = 0;
  ll i = 4;
  for (ll y = 2; y <= MAX / 2; ++y) {
    ll k = (y - 1) * (i - 1 - y);
    tmemo[i] = tmemo[i - 1] + k;
    ++i;
    tmemo[i] = tmemo[i - 1] + k + (y - 1);
    ++i;
  }
  int n;
  while (cin >> n, n >= 3) {
    cout << tmemo[n] << endl;
  }
}
