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
  int n;
  cin >> n;
  if (n <= 3) {
    printf("NO\n");
    return 0;
  }
  printf("YES\n");
  int f;
  if (n % 2 == 1) {
    printf("5 * 4 = 20\n");
    printf("20 - 1 = 19\n");
    printf("19 + 2 = 21\n");
    printf("21 + 3 = 24\n");
    f = 6;
  } else {
    printf("1 * 2 = 2\n");
    printf("2 * 3 = 6\n");
    printf("6 * 4 = 24\n");
    f = 5;
  }
  for (int i = f; i < n; i += 2) {
    printf("%d - %d = 1\n", i + 1, i);
    printf("24 * 1 = 24\n");
  }
}

