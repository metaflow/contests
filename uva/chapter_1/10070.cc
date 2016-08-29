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

int mod(string &s, int m) {
  int r = 0;
  for (auto c = s.cbegin(); c != s.cend(); c++) {
    r = (r * 10 + (*c - '0')) % m;
  }
  return r;
}

int main() {
  string y;
  bool first = true;
  while (cin >> y) {
    if (!first) cout << endl; first = false;
    bool leap = (mod(y, 4) == 0 && mod(y, 100) != 0) || (mod(y, 400) == 0);
    bool huluculu = (mod(y, 15) == 0);
    bool bulukulu = leap && (mod(y, 55) == 0);
    bool ordinary = !(leap || huluculu);
    if (ordinary) {
      cout << "This is an ordinary year." << endl;
    } else {
      if (leap) cout << "This is leap year." << endl;
      if (huluculu) cout << "This is huluculu festival year." << endl;
      if (bulukulu) cout << "This is bulukulu festival year." << endl;
    }
  }
}
