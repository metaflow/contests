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
  string s;
  getline(cin, s); getline(cin, s);
  while (tcc--) {
    double d = 0;
    getline(cin, s); // skip hangar coords
    while (true) {
      getline(cin, s);
      if (s == "") break;
      stringstream ss(s);
      double x1, x2, y1, y2;
      ss >> x1 >> y1 >> x2 >> y2;
      d += pow(pow(x1 - x2, 2) + pow(y1 - y2, 2), 0.5);
    }
    int mins = round(d * 2 * 60 / 20000);
    printf("%d:%02d\n", mins / 60, mins % 60);
    if (tcc) printf("\n");
  }
}
