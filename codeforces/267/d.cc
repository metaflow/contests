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

struct node;

map<string, int> dict;
vector<ii> values;
vector<vector<int>> edges;
vector<bool> visited;

int index(string s) {
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  if (dict.count(s) == 0) {
    dict[s] = dict.size() - 1;
    int r = 0;
    for (auto c : s) if (c == 'r') ++r;
    values.push_back(ii(r, s.size()));
    edges.resize(dict.size());
    visited.push_back(false);
  }
  return dict[s];
}

void walk(int start) {
  queue<int> q;
  q.push(start);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    visited[u] = true;
    ii w = values[u];
    for (auto v : edges[u]) {
      if (values[v] <= w) continue;
      values[v] = w;
      q.push(v);
    }
  }
}

int main() {
  int n, m;
  cin >> n;
  vi v;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    v.push_back(index(s));
  }
  cin >> m;
  for (int i = 0; i < m; ++i) {
    string a, b;
    cin >> a >> b;
    int u = index(a);
    int v = index(b);
    edges[v].push_back(u);
  }

  for (int i = 0; i < visited.size(); ++i) {
    if (visited[i]) continue;
    walk(i);
  }

  int count = 0, size = 0;
  for (auto i : v) {
    count += values[i].first;
    size += values[i].second;
  }

  cout << count << " " << size << endl;
}

