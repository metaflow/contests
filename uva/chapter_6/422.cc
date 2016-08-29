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
  int n;
  cin >> n;
  while (n) {
    vector<string> h(n);
    for (int i = 0; i < n; ++i) cin >> h[i];
    vector<vector<ii>> char_position(26);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        char_position[h[i][j] - 'A'].emplace_back(i, j);
      }
    }

    vector<string> words;
    string w;
    while (true) {
      cin >> w;
      if (w[0] >= 'A' && w[0] <= 'Z') {
        words.emplace_back(w);
        continue;
      }
      n = atoi(w.c_str());
      break;
    }

    for (auto s : words) {
      bool ok = false;
      int q = s.size() - 1;
      for (auto f : char_position[s[0] - 'A']) {
        for (auto t : char_position[s[q] - 'A']) {
          ok = false;
          if ((f.first == t.first) ||
            (f.first + f.second == t.first + t.second) ||
            (f.first - f.second == t.first - t.second)) {
            ok = (abs(f.second - t.second) == q);
          }
          if (f.second == t.second) {
            ok = (t.first - f.first == q);
          }
          if (!ok) continue;
          int di = 0;
          if (f.first < t.first) di = 1;
          if (f.first > t.first) di = -1;
          int dj = 0;
          if (f.second < t.second) dj = 1;
          if (f.second > t.second) dj = -1;
          int i = f.first;
          int j = f.second;
          int c = 0;
          while (ok && (i != t.first || j != t.second)) {
            ok = s[c] == h[i][j];
            i += di;
            j += dj;
            ++c;
          }
          if (ok) {
            printf("%d,%d %d,%d\n",
              f.first+1, f.second+1, t.first+1, t.second +1);
            break;
          }
        }
        if (ok) break;
      }
      if (!ok) printf("Not found\n");
    }
  }
}

//time : 49:43 (messy implementation)
