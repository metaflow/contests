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
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
using ii = pair<int, int>;

const int MAX = 102;

char img[MAX][MAX];
int n;

void fill(int x, int y) {
  stack<ii> s;
  s.push(make_pair(x, y));
  while (!s.empty()) {
    ii p = s.top();
    s.pop();
    int a = p.first;
    int b = p.second;
    if (a < 0 || a >= n || b < 0 || b >= n) continue;
    char &v = img[a][b];
    if (v == '.') continue;
    v = '.';
    s.push(make_pair(a - 1, b));
    s.push(make_pair(a + 1, b));
    s.push(make_pair(a, b - 1));
    s.push(make_pair(a, b + 1));
  }
}

int main() {
  int tcc;
  scanf("%d", &tcc);
  for (int tc = 1; tc <= tcc; ++tc) {
    scanf("%d\n", &n);
    for (int i = 0; i < n; ++i) {
      fgets(&img[i][0], n + 2, stdin);
    }
    int count = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (img[i][j] != 'x') continue;
        fill(i, j);
        count++;
      }
    }
    printf("Case %d: %d\n", tc, count);
  }
}
