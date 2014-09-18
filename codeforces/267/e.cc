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

vi B;
vi V;

const int MAX = 500000;

int memo[MAX];
bool pick[MAX];

int go(int n) {
  if (n < 3) return 0;

  int &r = memo[n];

  if (r == -1) {
    int b = B[n];
    if (b == n - 1) b = B[b];
    int t = -1;
    while (b != -1) {
      for (int c = n - 1; c > b; --c) {
        int a = B[c];
        while (a != -1 && a >= b) a = B[a];
        if (a != -1 && a > t) {
          t = a;
        }
      }
      b = B[b];
      if (b <= t) b = -1;
    }
    if (t != -1) {
      r = go(t - 1) + 4;
    }
    int o = go(n - 1);
    if (r > o) {
      pick[n] = true;
    } else {
      r = o;
    }
  }

  return r;
}

vi solution;

void construct(int n, int p) {
  if (n < 0) return;
  if (!pick[n]) {
    construct(n - 1, p);
    return;
  }

  int y = V[n];
  int b = B[n];
  if (b == n - 1) b = B[b];
  int x;
  int t = -1;
  while (b != -1) {
    for (int c = n - 1; c > b; --c) {
      int a = B[c];
      while (a != -1 && a >= b) a = B[a];
      if (a != -1 && a > t) {
        t = a;
        x = V[t];
      }
    }
    b = B[b];
    if (b <= t) b = -1;
  }
  solution[p--] = y;
  solution[p--] = x;
  solution[p--] = y;
  solution[p--] = x;
  construct(t - 1, p);
}

int main() {
  int n;
  cin >> n;
  map<int, int> m;
  V.resize(n);
  B.resize(n);

  fill(&memo[0], &memo[n], -1);
  fill(&pick[0], &pick[n], false);

  for (int i = 0; i < n; ++i) {
    cin >> V[i];
    if (m.count(V[i]) == 0) {
      B[i] = -1;
    } else {
      B[i] = m[V[i]];
    }
    m[V[i]] = i;
  }

  int k = go(n - 1);
  solution.resize(k);
  construct(n - 1, k - 1);

  printf("%d\n", k);
  for(int i = 0; i < k; ++i) {
    if (i != 0) printf(" ");
    printf("%d", solution[i]);
  }
  printf("\n");
}

