#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 41;

using vb = vector<int>;
int n;
int state[MAX];
int result;
int bound;
ll ops = 0;
int next_bound;

int displacement[MAX][MAX];
int moves[MAX][MAX];

bool dfs(int g, int tabu, int estimation, int king) {
  // ops++;
  if (estimation == 0) {
    result = g;
    return true;
  }
  if (g + estimation > bound) {
    next_bound = min(next_bound, g + estimation);
    return false;
  }
  g++;
  int m = moves[king][0];
  for (int j = 1; j < m; j++) {
    int &k = moves[king][j];
    if (k == tabu) continue;
    int de = displacement[king][state[k]] - displacement[k][state[k]];
    swap(state[k], state[king]);
    if (dfs(g, king, estimation + de, k)) return true;
    swap(state[k], state[king]);
  }
  return false;
}

int ida(int king) {
  int estimation = 0;
  for (int i = 0; i < n; i++) {
    if (i == king) continue;
    estimation += displacement[i][state[i]];
  }
  bound = estimation;
  result = INF;
  while (true) {
    next_bound = INF;
    if (dfs(0, -1, estimation, king)) break;
    bound = next_bound;
  }
  return result;
}

int main() {
   // lookups for estimations
  for (int i = 0; i < 40; i++) {
    for (int f = 2; f <= 40; f++) {
      int d = abs(i - f + 1);
      displacement[i][f] = abs(i / 4 - (f - 1) / 4) + min(d % 4, 4 - d % 4);
    }
  }

  int tc = 0;
  while (cin >> n, n) {
  // lookups for moves
    fill(&moves[0][0], &moves[MAX][0], 0);
    int king;
    for (king = 0; king < n; king++) {
      int &j = moves[king][0] = 1;
      for (int i = -4; i <= 4; i++) {
        if (i == 0 || i == 2 || i == -2) continue;
        int k = king + i;
        if (k < 0 || k >= n) continue;
        if (i > -4 && i < 4 && k / 4 != king / 4) continue;
        moves[king][j] = k;
        j++;
      }
    }

    for (int i = 0; i < n; i++) {
      cin >> state[i];
      // scanf("%d", &state[i]);
      if (state[i] == 1) king = i;
    }

    tc++;
    printf("Set %d:\n%d\n", tc, ida(king));
  }
  // cerr << ops << " ops" << endl;
}
