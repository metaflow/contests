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

const int MAX = 51;

int m[MAX][MAX];

list<ii> path;

void euler(list<ii>::iterator it, int c) {
  for (int i = 1; i < MAX; ++i) {
    if (m[c][i] == 0) continue;
    m[c][i]--;
    m[i][c]--;
    euler(path.insert(it, ii(i, c)), i);
  }
}

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; ++tc) {
    if (tc != 1) printf("\n");
    fill(&m[0][0], &m[MAX][0], 0);
    int n;
    cin >> n;
    while (n--) {
      int a, b;
      cin >> a >> b;
      m[a][b]++; m[a][0]++;
      m[b][a]++; m[b][0]++;
    }

    bool ok = true;
    for (int i = 0; i < MAX; ++i) {
      if (m[i][0] % 2 == 1) {
        ok = false;
        break;
      }
    }

    printf("Case #%d\n", tc);
    if (ok) {
      int j = 0; while (m[j][0] == 0) ++j;
      path.clear();
      euler(path.begin(), j);
      for (auto p : path) {
        printf("%d %d\n", p.first, p.second);
      }
    } else {
      printf("some beads may be lost\n");
    }
  }
}
