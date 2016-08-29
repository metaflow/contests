#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX_N = 100;
const int MAX_ROW = 20;

int N, R;
int M[MAX_N][MAX_N], E[MAX_N][MAX_N];
int row[MAX_ROW];
int bound, next_bound;
int result;

void fw() {
  memcpy(E, M, MAX_N * MAX_N * sizeof(int));
  for (int k = 0; k < R; k++) {
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < R; j++) {
        if (E[row[i]][row[k]] == 0 || E[row[k]][row[j]] == 0) continue;
        int t = E[row[i]][row[k]] + E[row[k]][row[j]];
        if (E[row[i]][row[j]]) t = min(t, E[row[i]][row[j]]);
        E[row[i]][row[j]] = t;
      }
    }
  }
}

int estimate(int p) {
  if (p == R - 2) {
    return M[row[p]][row[R - 1]];
  }
  int m = 0;
  for (int i = p + 1; i < R - 1; i++) {
     m = max(m, E[row[p]][row[i]] + E[row[i]][row[R - 1]]);
  }
  return m;
}

bool dfs(int g, int pos) {
  int e = estimate(pos);
  if (e == 0) return false;
  if (e + g > bound) {
    next_bound = min(next_bound, e + g);
    return false;
  }
  if (pos == R - 2) {
    result = g + e;
    return true;
  }
  for (int i = pos + 1; i < R - 1; i++) {
    int t = M[row[pos]][row[i]];
    if (t == 0) continue;
    swap(row[pos + 1],row[i]);
    if (dfs(g + t, pos + 1)) return true;
    swap(row[pos + 1],row[i]);
  }
  return false;
}

int ida() {
  bound = estimate(0);
  result = 0;
  while (true) {
    next_bound = INF;
    if (dfs(0, 0)) break;
    if (next_bound == INF) break;
    bound = next_bound;
  }
  return result;
}

int main() {
  ios_base::sync_with_stdio(false);
  int row_count;
  cin >> N >> row_count;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> M[i][j];
    }
  }
  string s;
  getline(cin, s);
  while (row_count--) {
    getline(cin, s);
    stringstream ss(s);
    int x;
    R = 0;
    while (ss >> x) {
      row[R++] = x - 1;
    }
    fw();
    cout << ida() << endl;
  }
}
