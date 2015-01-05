#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 200010;
const int LMAX = 20;

int position[MAX];
int length[MAX];
int reach[MAX];
int cost[MAX][LMAX];
int ub[MAX][LMAX];

int main() {
  int n;
  while (cin >> n) {
    for (int i = 0; i < n; i++) cin >> position[i] >> length[i];
    stack<int> s;
    for (int i = n - 1; i >= 0; i--) {
      reach[i] = position[i] + length[i];
      while (!s.empty() && position[s.top()] <= reach[i]) {
        reach[i] = max(reach[i], reach[s.top()]);
        s.pop();
      }
      s.push(i);
    }

    fill(&ub[0][0], &ub[MAX][0], n);
    fill(&cost[0][0], &cost[MAX][0], 0);

    for (int i = 0; i < n; i++) {
      auto p = upper_bound(position, position + n, reach[i]);
      int j = p - position;
      ub[i][0] = j;
      if (j != n) cost[i][0] = position[j] - reach[i];
    }

    int y;
    for (y = 0; (1 << y) <= n; y++);

    for (int k = 1; k < y; k++) {
      for (int i = 0; i < n; i++) {
        int u = ub[i][k - 1];
        ub[i][k] = ub[u][k - 1];
        cost[i][k] = cost[i][k - 1] + cost[u][k - 1];
      }
    }

    int q;
    cin >> q;
    while (q--) {
      int f, t;
      cin >> f >> t; f--; t--;
      int c = 0;
      while (t >= ub[f][0]) {
        for (int k = y; k >= 0; k--) {
          if (ub[f][k] > t) continue;
          c += cost[f][k];
          f = ub[f][k];
          break;
        }
      }
      cout << c << endl;
    }
  }
}
