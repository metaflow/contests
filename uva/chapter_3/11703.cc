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
const int MAX = 1000000;
int memo[MAX + 1];

int get(int x) {
  int &r = memo[x];
  if (r == 0) {
    r = get(x - sqrt(x)) + get(log(x)) + get(x * sin(x) * sin(x));
    r %= 1000000;
  }
  return r;
}

int main() {
  fill(memo, memo + MAX + 1, 0);
  memo[0] = 1;
  int x;
  while (scanf("%d", &x), x != -1) {
    printf("%d\n", get(x));
  }
}
