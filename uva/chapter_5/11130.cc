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
  int a, b, v, g, s;
  while (cin >> a >> b >> v >> g >> s, a != 0) {
    double d = v * s / 2;
    double r = double(g) * M_PI / 180;
    double da = d * cos(r);
    double db = d * sin(r);
    int cv = floor(0.5 + da / double(a));
    int ch = floor(0.5 + db / double(b));
    printf("%d %d\n", cv, ch);
  }
}

