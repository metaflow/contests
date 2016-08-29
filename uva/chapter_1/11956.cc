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
  int tcc, tc;
  string s;

  cin >> tcc;
  for (tc = 1; tc <= tcc; tc++) {
    printf("Case %d:", tc);
    cin >> s;
    int p = 0;
    vector<int> v(100);
    for (auto c : s) {
      switch (c) {
        case '>': p = (p + 1) % 100; break;
        case '<': p = (p - 1 + 100) % 100; break;
        case '+': v[p] = (v[p] + 1) % 256; break;
        case '-': v[p] = (v[p] - 1 + 256) % 256; break;
      }
    }
    for (auto i : v) printf(" %02X", i);
    printf("\n");
  }
}
