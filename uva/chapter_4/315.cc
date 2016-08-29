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

struct node {
  int age, low;
  bool visited;
  int parent = -1;
  bool articulation;
  vi adjusted;
};

int T = 0;

void mark_adjusted(vector<node> &G, int from) {
  node &x = G[from];
  x.visited = true;
  x.age = x.low = ++T;
  int children = 0;
  for (auto i : x.adjusted) {
    node &y = G[i];

    if (y.visited) {
      if (i != x.parent) x.low = min(x.low, y.age);
      continue;
    }
    y.parent = from;
    mark_adjusted(G, i);
    x.low = min(x.low, y.low);

    if (x.parent == -1) {
      ++children;
      x.articulation |= children > 1;
    } else {
      x.articulation |= y.low >= x.age;
    }
  }
}

void dfs(vector<node> &G, int start) {
  G[start].visited = true;
  for (auto i : G[start].adjusted) {
    if (G[i].visited) continue;
    dfs(G, i);
  }
}

int main() {
  int n;
  while (cin >> n, n) {
    vector<node> G(n);
    string s;
    while (getline(cin, s)) {
      istringstream ss(s);
      int f;
      if (!(ss >> f)) continue;
      if (f == 0) break;
      --f;
      int t;
      while (ss >> t) {
        --t;
        G[f].adjusted.push_back(t);
        G[t].adjusted.push_back(f);
      }
    }
    mark_adjusted(G, 0);
    int count = 0;
    for (auto n : G) {
      if (n.articulation) ++count;
    }
    // int count = 0;
    // for (int i = 0; i < G.size(); ++i) {
    //   for (auto &n : G) n.visited = false;
    //   G[i].visited = true;
    //   dfs(G, (i + 1) % G.size());
    //   for (auto n : G) {
    //     if (n.visited) continue;
    //     ++count;
    //     break;
    //   }
    // }
    cout << count << endl;
  }
}
