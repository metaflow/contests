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

const int MAX = 100;
bool edge[MAX][MAX];
bool visited[MAX];
stack<int> topological_order;

int m, n;

void dfs(int from) {
  visited[from] = true;
  for (int i = 0; i < n; ++i) {
    if (visited[i]) continue;
    if (!edge[from][i]) continue;
    dfs(i);
  }
  topological_order.push(from + 1);
}

int main() {
    while (cin >> n >> m, n) {
      fill(&edge[0][0], &edge[MAX][0], false);
      fill_n(visited, MAX, false);
      while (m--) {
        int a, b;
        cin >> a >> b;
        edge[a - 1][b - 1] = true;
      }
      for (int i = 0; i < n; ++i) {
        if (!visited[i]) dfs(i);
      }
      cout << topological_order.top();
      topological_order.pop();
      while (!topological_order.empty()) {
        cout << " " << topological_order.top();
        topological_order.pop();
      }
      cout << endl;
    }
}
