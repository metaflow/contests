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
  vi a(10, 0);
  for (int i = 0; i < 6; ++i) {
    int x;
    cin >> x;
    a[x]++;
  }
  bool alien = true;
  for (int i = 0; i < 10; ++i) {
    if (a[i] >= 4) {
      alien = false;
      a[i] -= 4;
    }
  };
  if (alien) {
    printf("Alien\n");
  } else {
    bool bear = true;
    for (int i = 0; i < 10; ++i) bear = bear && (a[i] < 2);
    if (bear) {
      printf("Bear\n");
    } else {
      printf("Elephant\n");
    }
  }
}
