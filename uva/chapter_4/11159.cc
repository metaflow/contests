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

const int MAX = 202;
const int sink = MAX - 1;
const int source = 0;

bool m[MAX][MAX];
bitset<MAX> visited;

bool augment(int from) {
  visited[from] = true;
  if (from == sink) return true;
  for (int i = 0; i < MAX; ++i) {
    if (!m[from][i] || visited[i]) continue;
    if (!augment(i)) continue;
    m[from][i] = false;
    m[i][from] = true;
    return true;
  }
  return false;
}

int max_flow() {
  int t = 0;
  while (true) {
    visited.reset();
    if (!augment(source)) break;
    ++t;
  }
  return t;
}

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; ++tc) {
    fill(&m[0][0], &m[MAX][0], false);
    int n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
      m[source][i + 1] = true;
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
      int x;
      cin >> x;
      int p = i + n + 1;
      for (int j = 0; j < a.size(); ++j) {
        if (a[j] == 0) {
          if (x == 0) m[j + 1][p] = true;
        } else {
          if (x % a[j] == 0) m[j + 1][p] = true;
        }
      }
      m[p][sink] = true;
    }

    printf("Case %d: %d\n", tc, max_flow());
  }
}
