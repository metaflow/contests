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

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;

const int MAX = 50002;
int edge[MAX], weight[MAX];
bool processing[MAX];

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; ++tc) {
    int n;
    cin >> n;
    fill_n(edge, n + 1, 0);
    fill_n(processing, n + 1, false);
    fill_n(weight, n + 1, 0);
    for (int i = 0; i < n; ++i) {
      int from, to;
      cin >> from >> to;
      edge[from] = to;
    }
    for (int i = 1; i <= n; ++i) {
      if (weight[i] != 0) continue;
      stack<int> s;
      s.push(i);
      while (!s.empty()) {
        int x = s.top();
        processing[x] = true;
        int y = edge[x];
        int w = 0;
        if (y == 0 || weight[y] != 0) {
          w = 1;
          if (y != 0) w += weight[y];
          weight[x] = w;
          processing[x] = false;
          s.pop();
          continue;
        }
        if (processing[y]) { // cycle
          stack<int> tmp;
          while (true) {
            tmp.push(s.top());
            processing[s.top()] = false;
            s.pop();
            ++w;
            if (tmp.top() == y) break;
          }
          while (!tmp.empty()) {
            weight[tmp.top()] = w;
            tmp.pop();
          }
          continue;
        }
        s.push(y);
      }
    }
    int m = 1;
    for (int i = 1; i <= n; i++) {
      if (weight[m] < weight[i]) m = i;
    }
    printf("Case %d: %d\n", tc, m);
  }
}
