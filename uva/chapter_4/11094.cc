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

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;

const int MAX = 20;
const int MAX_AREAS = MAX * MAX;
int world[MAX][MAX];
int h, w;

void fill(int x, int y, int to) {
  int from = world[x][y];
  stack<ii> s;
  s.push(make_pair(x, y));
  while (!s.empty()) {
    ii p = s.top();
    s.pop();
    int a = p.first;
    int b = p.second;
    if (a < 0 || a >= h) continue;
    int &m = world[a][b];
    if (m != from) continue;
    m = to;
    s.push(make_pair(a + 1, b));
    s.push(make_pair(a - 1, b));
    s.push(make_pair(a, (b + 1 + w) % w));
    s.push(make_pair(a, (b - 1 + w) % w));
  }
}

int main() {
  int sizes[MAX_AREAS];
  while (cin >> h >> w) {
    fill(&world[0][0], &world[MAX][0], 0);
    fill_n(sizes, MAX_AREAS, 0);
    for (int i = 0; i < h; ++i) {
      string s;
      cin >> s;
      for (int j = 0; j < w; ++j) world[i][j] = (int) s[j];
    }
    int x, y;
    cin >> x >> y;
    int land = world[x][y];
    fill(x, y, 0);
    int mark = -1;
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        if (world[i][j] != land) continue;
        fill(i, j, mark);
        --mark;
      }
    }
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        cerr << world[i][j] << " ";
        if (world[i][j] >= 0) continue;
        ++sizes[-world[i][j]];
      }
      cerr << endl;
    }
    int m = 0;
    for (int i = 1; i < -mark; ++i) m = max(m, sizes[i]);
    cout << m << endl;
  }
}
