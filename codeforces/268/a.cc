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
  int n, p;
  cin >> n >> p;
  vector<bool> b(n, false);
  while (p--) {
    int x;
    cin >> x;
    --x;
    b[x] = true;
  }
  cin >> p;
  while (p--) {
    int x;
    cin >> x;
    --x;
    b[x] = true;
  }
  bool ok = true;
  for (int i = 0; i < n; ++i) {
    ok = ok && b[i];
  }
  if (ok) {
    cout << "I become the guy." << endl;
  } else {
    cout << "Oh, my keyboard!" << endl;
  }
}
