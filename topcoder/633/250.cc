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

class PeriodicJumping {
public:
  int minimalTime(int x, vector <int> jumpLengths) {
    x = abs(x);
    int a = 0, b = 0;
    int t = 0;
    int d[4];
    int c = 0;
    while (x < a || x > b) {
      int j = jumpLengths[t % jumpLengths.size()];
      ++t;
      d[0] = abs(a - j);
      d[1] = abs(a + j);
      d[2] = abs(b - j);
      d[3] = abs(b + j);
      if (j >= a && j <= b) {
        a = 0;
      } else {
        a = d[0];
      }
      b = d[0];
      for (int i = 1; i < 4; ++i) {
        a = min(d[i], a);
        b = max(d[i], b);
      }
      if (t % jumpLengths.size() == 0 && a == 0 && c == 0 && b != 0) {
        int k = x / b;
        t = k * t;
        b *= k;
        c = 1;
      }
    }
    return t;
  }
};

int main() {
  PeriodicJumping p;
  cout << p.minimalTime(15, {1,2,3,4,5,6,7,8,9,10}) << endl;
  cout << p.minimalTime(5, {5}) << endl;
  cout << p.minimalTime(1, {10}) << endl;
  cout << p.minimalTime(-1000000000, {1}) << endl;
  cout << p.minimalTime(-10, {2,3,4,500,6,7,8}) << endl;
  cout << p.minimalTime(0, {166694}) << endl;
}
