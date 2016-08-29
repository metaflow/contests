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

struct node {
  int color;
  vi adjusted;
};

int main() {
    int v;
    while (cin >> v, v) {
      vector<node> G(v);
      int a, b;
      while (cin >> a >> b, a) {
        --a;
        --b;
        G[a].adjusted.push_back(b);
        G[b].adjusted.push_back(a);
      }
      bool ok = true;
      for (int i = 0; i < v && ok; ++i) {
        if (G[i].color != 0) continue;
        stack<int> s;
        s.push(i);
        G[i].color = 1;
        while (ok && !s.empty()) {
          int x = s.top();
          s.pop();
          for (auto y : G[x].adjusted) {
            if (G[y].color == 0) {
              G[y].color = -G[x].color;
              s.push(y);
              continue;
            }
            if (G[y].color == G[x].color) {
              ok = false;
              break;
            }
          }
        }
      }

      if (ok) {
        printf("YES\n");
      } else {
        printf("NO\n");
      }
    }
}
