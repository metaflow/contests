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

const int MAX = 27;

llu A[MAX], B[MAX];

llu a(int n) {
  if (n <= 2) return 1;
  llu &r = A[n];
  if (r == 0) {
    r = a(n - 1) * 3; // x(A), xA, (A)x
    for (int i = 2; i <= n - 2; ++i) {
      r += 2 * a(i) * a(n - i); // (x.. i ..x)A, (xx.. i ..x)(A)
    }
  }
  return r;
}

llu b(int n) {
  if (n <= 2) return 1;
  llu &r = B[n];
  if (r == 0) {
    r = 0;
    for (int i = 1; i < n; ++i) r += b(i) * b(n - i);
  }
  return r;
}

llu f(int n) {
  return a(n) - b(n);
}

int main() {
  fill_n(A, MAX, 0);
  fill_n(B, MAX, 0);
  int n;
  while (cin >> n) printf("%llu\n", f(n));
}
