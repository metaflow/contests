#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max() / 2;
const int MAX = 50;

map<string, int> name_index;

int get_index(string name) {
  if (name_index.count(name) == 0) {
    int i = name_index.size();
    name_index[name] = i;
  }
  return name_index[name];
}

int main() {
  int tc = 0;
  int V, E;
  int m[MAX][MAX];
  while (cin >> V >> E, V) {
    tc++;
    name_index.clear();
    fill(&m[0][0], &m[MAX][0], INF);
    for (int i = 0; i < V; i++) m[i][i] = 0;
    for (int i = 0; i < E; i++) {
      string a, b;
      cin >> a >> b;
      int u = get_index(a);
      int v = get_index(b);
      m[u][v] = m[v][u] = 1;
    }

    for (int k = 0; k < V; k++)
    for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++) m[i][j] = min(m[i][j], m[i][k] + m[k][j]);

    int d = 0;
    for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++) d = max(d, m[i][j]);
    if (d == INF) {
      printf("Network %d: DISCONNECTED\n\n", tc);
    } else {
      printf("Network %d: %d\n\n", tc, d);
    }
  }
}
