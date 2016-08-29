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

int f(int a) {
  return ((a * a) / 100) % 10000;
}

int uniq(int n) {
  int r = n, t = n;
  while (true) {
    r = f(f(r));
    t = f(t);
    if (r == t) break;
  }

  int s = 0;
  r = n;
  while (r != t) {
    r = f(r);
    t = f(t);
    ++s;
  }

  int c = 0;
  r = t;
  while (true) {
    r = f(r);
    ++c;
    if (r == t) break;
  }

  return c + s;
}

int main() {
  int n;
  while (cin >> n, n) {
    cout << uniq(n) << endl;
  }
}

// time: 18:44
