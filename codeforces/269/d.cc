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

vi back;

void prepare(vi &E) {
  back.resize(E.size());
  int i = 0;
  int j = -1;
  back[0] = j;
  while (i < E.size()) {
    while (j >= 0 && E[j] != E[i]) j = back[j];
    ++j; ++i;
    back[i] = j;
  }
}

int count_matches(vi &B, vi &E) {
  int i = 0;
  int j = 0;
  int c = 0;
  while (i < B.size()) {
    while (j >= 0 && B[i] != E[j]) j = back[j];
    ++i; ++j;
    if (j == E.size()) {
      j = back[j];
      ++c;
    }
  }
  return c;
}

int main() {
  int n, w, i;
  cin >> n >> w;
  --n; --w;
  vi B, E;
  ll v, t;
  cin >> v;
  for (i = 0; i < n; ++i) {
    cin >> t;
    B.emplace_back(t - v);
    v = t;
  }
  cin >> v;
  for (i = 0; i < w; ++i) {
    cin >> t;
    E.emplace_back(t - v);
    v = t;
  }
  if (n == 0 || w == 0) {
    if (w == 0) {
      cout << (n + 1) << endl;
    } else {
      cout << 0 << endl;
    }
  } else {
    prepare(E);
    cout << count_matches(B, E) << endl;
  }
}
