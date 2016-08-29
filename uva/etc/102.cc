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
  vector<int> a(9);
  int i, j;
  string names = "BGC";
  while (cin >> a[0]) {
    int sum = a[0];
    for (i = 1; i < 9; i++) {
      cin >> a[i];
      sum += a[i];
    }
    int b = sum;
    string bn = "BCG";
    for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++) {
      if (i == j) continue;
      int s = sum - (a[i] + a[j + 3] + a[3 - i - j + 6]);
      string n = string("") + names[i] + names[j] + names[3 - i - j];
      if (s < b || (s == b && n < bn)) { b = s; bn = n; }
    }
    cout << bn << " " << b << endl;
  }
}
