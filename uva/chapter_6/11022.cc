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
string s;

const int MAX = 81;

int memo[MAX][MAX];

int reduction(int f, int t) {
  int x = t - f;
  if (x == 1) return 1;
  int &r = memo[f][t];
  if (r == INF) {
    // try to reduce
    for (int i = 1; i < x; ++i) {
      if (x % i != 0) continue;
      bool ok = true;
      for (int j = i; j < x; ++j) {
        if (s[f + j] != s[f + (j % i)]) {
          ok = false;
          break;
        }
      }
      if (!ok) continue;
      r = min(r, reduction(f, f + i));
    }
    // try split
    for (int i = f + 1; i < t; ++i) {
      r = min(r, reduction(f, i) + reduction(i, t));
    }
  }
  return r;
}

int main() {
  while (true) {
    cin >> s;
    if (s == "*") break;
    fill(&memo[0][0], &memo[MAX][0], INF);
    cout << reduction(0, s.size()) << endl;
  }
}

// time : 55:31 implementation mistake
