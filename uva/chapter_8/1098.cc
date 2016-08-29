#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 8;

struct check_point {
  int x, y, t;
};

check_point cp[2];
const int dx[] = { 1, -1, 0, 0 };
const int dy[] = { 0, 0, 1, -1 };
bool field[MAX][MAX];
int n, m;
llu full;
llu future_checkpoints;

const llu set_field(const llu field, const int x, const int y) {
  return field | (1llu << (x * m + y));
}

const bool field_is_set(const llu field, const int x, const int y) {
  return field & (1llu << (x * m + y));
}

bool connected(llu field) {
  queue<pair<int, int>> q;
  field = set_field(field, 0, 1);
  q.emplace(0, 1);
  while (!q.empty()) {
    auto p = q.front(); q.pop();
    for (int i = 0; i < 4; i++) {
      int x = p.first + dx[i];
      int y = p.second + dy[i];
      if (x < 0 || x >= n || y < 0 || y >= m ||
          field_is_set(field, x, y)) continue;
      field = set_field(field, x, y);
      q.emplace(x, y);
    }
  }
  return field == full;
}

int add;
unordered_map<llu, llu> counts;
check_point target;

void dfs(int x0, int y0, int t, const llu field) {
  // if (t == target.t) {
  //   counts[field] += add;
  //   return;
  // }
  t++;
  for (int i = 0; i < 4; i++) {
    int x = x0 + dx[i];
    int y = y0 + dy[i];
    if (x < 0 || x >= n || y < 0 || y >= m ||
        field_is_set(field, x, y) ||
        field_is_set(future_checkpoints, x, y)) continue;
    int dt = target.t - t;
    int d = abs(target.x - x) + abs(target.y - y);
    if (d == 0) {
      if (dt == 0) counts[set_field(field, x, y)] += add;
      continue;
    }
    if (d > dt) continue;
    llu u = set_field(field, x, y);
    if (connected(u)) {
      dfs(x, y, t, u);
    }
  }
}

int main() {
  int tc = 0;
  while (cin >> n >> m, n != 0) {
    tc++;
    check_point cp[5];
    cp[0].x = 0;
    cp[0].y = 0;
    cp[0].t = 1;
    for (int i = 1; i < 4; i++) {
      cin >> cp[i].x >> cp[i].y;
      cp[i].t = m * n * i / 4;
    }
    cp[4].x = 0;
    cp[4].y = 1;
    cp[4].t = m * n;

    full = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        full = set_field(full, i, j);
      }
    }

    unordered_map<llu, llu> a;
    a[set_field(0, 0, 0)] = 1;
    for (int i = 0; i < 4; i++) {
      auto from = cp[i];
      auto to = cp[i + 1];
      future_checkpoints = 0;
      for (int j = i + 2; j < 5; j++) {
        future_checkpoints = set_field(future_checkpoints, cp[j].x, cp[j].y);
      }
      counts.clear();
      target = to;
      for (auto s : a) {
        add = s.second;
        dfs(from.x, from.y, from.t, s.first);
      }
      swap(a, counts);
    }
    printf("Case %d: %llu\n", tc, a[full]);
  }
}
