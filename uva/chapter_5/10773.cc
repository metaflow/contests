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
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; ++tc) {
    double p, v, u;
    cin >> p >> v >> u;
    printf("Case %d: ", tc);
    if (v == 0 || u == 0 || u <= v) {
      printf("can't determine\n");
    } else {
      double t1 = p / u;
      double t2 = p / pow(pow(u, 2) - pow(v, 2), 0.5);
      double d = t2 - t1;
      d = round(d * 1000) / 1000;
      printf("%.3f\n", d);
    }
  }
}
