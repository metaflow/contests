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

vector<string> names;
map<string, int> dict;

int get_index(string &s) {
  if (dict.count(s) == 0) {
    dict[s] = names.size();
    names.emplace_back(s);
  }
  return dict[s];
}

int main() {
  int i, j, k, n, m, tc;
  string e1, e2;
  tc = 0;
  while (cin >> n, n) {
    tc++;
    dict.clear();
    names.clear();
    vector<ii> connections;
    while (n--) {
      cin >> k >> e1;
      get_index(e1); // if it's the only event
      for (i = 1; i < k; i++) {
        cin >> e2;
        connections.emplace_back(get_index(e1), get_index(e2));
        e1 = e2;
      }
    }
    cin >> n;
    while (n--) {
      cin >> e1 >> e2;
      connections.emplace_back(get_index(e1), get_index(e2));
    }
    m = names.size();
    vector<vector<bool>> w(m);
    for (auto &v : w) v.resize(m, false);
    for (auto c : connections) w[c.first][c.second] = true;

    for (k = 0; k < m; k++)
    for (i = 0; i < m; i++)
    for (j = 0; j < m; j++) w[i][j] = w[i][j] || (w[i][k] && w[k][j]);

    vector<ii> concurrent;
    for (i = 0; i < m; i++)
    for (j = i + 1; j < m; j++) {
      if (w[i][j] || w[j][i]) continue;
      concurrent.emplace_back(i, j);
    }

    if (concurrent.empty()) {
      printf("Case %d, no concurrent events.\n", tc);
    } else {
      printf("Case %d, %lu concurrent events:\n", tc, concurrent.size());
      for (i = 0; i < 2 && i < (int)concurrent.size(); i++) {
        printf("(%s,%s) ", names[concurrent[i].first].c_str(),
                          names[concurrent[i].second].c_str());
      }
      printf("\n");
    }
  }
}
