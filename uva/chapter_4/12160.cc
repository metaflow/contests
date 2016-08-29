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
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <queue>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;

const int MAX = 10000;
const int INF = numeric_limits<int>::max();
int m[MAX];

int main() {
  int tc = 0;
  int s, t, n;
  while (cin >> s >> t >> n, n) {
    fill_n(m, MAX, INF);
    vi v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    queue<int> q;
    q.push(s);
    m[s] = 0;
    int result = INF;
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      if (x == t) {
        result = m[x];
        break;
      }
      for (auto d : v) {
        int y = (x + d) % 10000;
        if (m[y] != INF) continue;
        m[y] = m[x] + 1;
        q.push(y);
      }
    }
    printf("Case %d: ", ++tc);
    if (result == INF) {
      printf("Permanently Locked\n");
    } else {
      printf("%d\n", result);
    }
  }
}
