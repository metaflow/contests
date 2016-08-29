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
  while (tcc--) {
    int n;
    cin >> n;
    int sum = 0;
    vi v(n);
    while (n--) cin >> v[n];
    for (auto i : v) sum += i;
    double above = 0;
    for (auto i : v) if (i * v.size() > sum) above++;
    above = round(above * 1000 * 100 / v.size()) / 1000;
    printf("%.3f%%\n", above);
  }
}
