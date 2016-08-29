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

const int MAX = 200;

int main() {
  int tcc;
  scanf("%d", &tcc);
  while (tcc--) {
    int m, c;
    scanf("%d%d", &m, &c);
    bool a[MAX + 1], b[MAX + 1];
    fill(a, a + MAX + 1, false);
    a[0] = true;
    while (c--) {
      int n;
      scanf("%d", &n);
      fill(b, b + MAX + 1, false);
      while (n--) {
        int v;
        scanf("%d", &v);
        for (int i = v; i <= MAX; ++i) {
          b[i] = b[i] || a[i - v];
        }
      }
      copy(b, b + MAX + 1, a);
    }
    while (!a[m] && m) m--;
    if (m) {
      printf("%d\n", m);
    } else {
      printf("no solution\n");
    }
  }
}
