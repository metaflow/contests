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
using ii = pair<int, int>;
using iii = tuple<int, int, int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 2002;
int w[MAX][26];

vector<vector<iii>> words;
map<string, int> language_index;

int dijkstra(int start, int finish) {
  fill(&w[0][0], &w[MAX][0], INF);
  int best = INF;
  priority_queue<iii, vector<iii>, greater<iii>> pq; // weight, lang, letter
  w[start][0] = 0;
  w[start][1] = 0;
  pq.push(iii(0, start, 0));
  pq.push(iii(0, start, 1));
  while (!pq.empty()) {
    int d = get<0>(pq.top());
    int u = get<1>(pq.top());
    int a = get<2>(pq.top());
    pq.pop();
    if (w[u][a] != d) continue;
    if (d >= best) continue;
    for (auto e : words[u]) {
      auto va = get<2>(e);
      if (va == a) continue;
      auto v = get<1>(e);
      auto ew = get<0>(e);
      if (w[v][va] <= d + ew) continue;
      w[v][va] = d + ew;
      if (v == finish) {
        best = min(best, w[v][va]);
      }
      pq.push(iii(w[v][va], v, va));
    }
  }
  return best;
}

int get_index(string a) {
  if (language_index.count(a) == 0) {
    language_index[a] = words.size();
    words.resize(words.size() + 1);
  }
  return language_index[a];
}

int main() {
  int n;
  while (cin >> n, n) {
    language_index.clear();
    words.clear();
    string a, b, c;
    cin >> a >> b;
    int start = get_index(a);
    int finish = get_index(b);
    while (n--) {
      cin >> a >> b >> c;
      int u = get_index(a);
      int v = get_index(b);
      int f = c[0] - 'a';
      int w = c.size();
      words[u].push_back(iii(w, v, f));
      words[v].push_back(iii(w, u, f));
    }
    int result = dijkstra(start, finish);
    if (result == INF) {
      cout << "impossivel" << endl;
    } else {
      cout << result << endl;
    }
  }
}


