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

vi count(int n) {
  vi c(10);
  for (int i = 1; i <= n; ++i) {
    int j = i;
    while (j) {
      c[j % 10]++;
      j /= 10;
    }
  }
  return c;
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int n;
    cin >> n;
    auto c = count(n);
    printf("%d", c[0]);
    for (int i = 1; i < 10; ++i) printf(" %d", c[i]);
    printf("\n");
  }
}
