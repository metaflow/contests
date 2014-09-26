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

int main() {
  vector<ii> p;
  int i, j;
  int n;
  cin >> n;
  for (i = 0; i < n; ++i) {
    cin >> j;
    p.push_back(ii(j, i + 1));
  }
  sort(p.begin(), p.end());
  int f = 0;
  while (f < n - 1 && p[f].first != p[f + 1].first) ++f;
  int s = f + 1;
  while (s < n - 1 && p[s].first != p[s + 1].first) ++s;
  if (s < n - 1) {
    printf("YES\n");
    printf("%d", p[0].second);
    for (i = 1; i < p.size(); ++i) printf(" %d", p[i].second);
    printf("\n");
    swap(p[f], p[f + 1]);
    printf("%d", p[0].second);
    for (i = 1; i < p.size(); ++i) printf(" %d", p[i].second);
    printf("\n");
    swap(p[s], p[s + 1]);
    printf("%d", p[0].second);
    for (i = 1; i < p.size(); ++i) printf(" %d", p[i].second);
    printf("\n");
  } else {
    printf("NO\n");
  }
}
