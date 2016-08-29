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
#include <queue>

using namespace std;
using vi = vector<int>;

struct node {
  int color;
  vi adjusted;
};

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int v, e;
    cin >> v >> e;
    vector<node> G(v);
    while (e--) {
      int f, t;
      cin >> f >> t;
      G[f].adjusted.push_back(t);
      G[t].adjusted.push_back(f);
    }
    bool ok = true;
    int result = 0;
    for (int start = 0; start < G.size() && ok; ++start) {
      if (G[start].color != 0) continue;
      queue<int> q;
      q.push(start);
      int ones = 0;
      int total = 0;
      G[start].color = 1;
      while (!q.empty() && ok) {
        total++;
        int x = q.front();
        if (G[x].color == 1) ++ones;
        q.pop();
        for (auto y : G[x].adjusted) {
          if (G[y].color == 0) {
            G[y].color = -G[x].color;
            q.push(y);
            continue;
          }
          if (G[y].color == G[x].color) {
            ok = false;
            break;
          }
        }
      }
      result += max(min(ones, total - ones), 1);
    }
    if (ok) {
      printf("%d\n", result);
    } else {
      printf("-1\n");
    }
  }
}
