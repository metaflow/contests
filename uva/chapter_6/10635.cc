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

const int MAX = 250*250 + 1;

int lp[MAX];

int lis(vi &q) {
  vi m;
  for (int i : q) {
    auto it = upper_bound(m.begin(), m.end(), i);
    if (it == m.end()) {
      m.push_back(i);
    } else {
      *it = i;
    }
  }
  return m.size();
}

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; ++tc) {
    int n, p, q;
    cin >> n >> p >> q;
    ++p; ++q;
    fill_n(lp, n * n + 1, -1);
    for (int i = 0; i < p; ++i) {
      int v;
      cin >> v;
      lp[v] = i;
    }
    vi iq;
    for (int i = 0; i < q; ++i) {
      int v;
      cin >> v;
      if (lp[v] == -1) continue;
      iq.push_back(lp[v]);
    }
    printf("Case %d: %d\n", tc, lis(iq));
  }
}

// time : 1:13:00 finding optimal solution
