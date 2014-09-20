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

vi v;
vi s; // 0 -> A, 1 -> B
vector<vector<int>> da, db;


bool roll(int n, int value, vector<vector<int>> &d, vi &modified) {
  modified.push_back(n);
  queue<int> q;
  q.push(n);
  bool ok = true;
  while (!q.empty() && ok) {
    int u = q.front(); q.pop();
    modified.push_back(u);
    s[u] = value;
    for (auto v : d[u]) {
      if (s[v] == 1 - value) {
        ok = false;
        break;
      }
      if (s[v] == value) continue;
      q.push(v);
    }
  }
  return ok;
}

bool backtrack(int n) {
  if (n < 0) return true;
  if (s[n] != -1) return backtrack(n - 1);

  if (da[n].empty()) {
    s[n] = 0;
    return backtrack(n - 1);
  }
  if (db[n].empty()) {
    s[n] = 1;
    return backtrack(n - 1);
  }

  vi modified;

  // trying A
  bool ok = roll(n, 0, da, modified);
  if (ok) ok = backtrack(n - 1);
  if (ok) return true;
  for (auto i : modified) s[i] = -1; // rollback

  modified.clear();

  // trying B
  ok = roll(n, 1, db, modified);
  if (ok) ok = backtrack(n - 1);
  if (ok) return true;
  for (auto i : modified) s[i] = -1; // rollback

  return false;
}

int main() {
  int n, a, b;
  cin >> n >> a >> b;
  v.resize(n);
  for (int i = 0; i < n; ++i) cin >> v[i];

  da.resize(n);
  db.resize(n);
  s.assign(n, -1);
  sort(v.begin(), v.end());
  vi mask(n, 3);

  bool ok = true;
  for (int i = 0; i < v.size(); ++i) {
    auto ita = lower_bound(v.begin(), v.end(), a - v[i]);
    if (ita != v.end() && (*ita == a - v[i])) {
      da[ita - v.begin()].push_back(i);
      da[i].push_back(ita - v.begin());
    } else {
      ita = v.end();
    }

    auto itb = lower_bound(v.begin(), v.end(), b - v[i]);
    if (itb != v.end() && (*itb == b - v[i])) {
      db[itb - v.begin()].push_back(i);
      db[i].push_back(itb - v.begin());
    } else {
      itb = v.end();
    }

    if (ita == v.end() && itb == v.end()) {
      ok = false;
      break;
    }

    vi modified;
    if (ita == v.end()) {
      s[i] = 1;
    }

    modified.clear();

    if (itb == v.end()) {
      s[i] = 0;
    }
  }

  for (int i = 0; i < n; ++i) {
    if (s[i] == -1) continue;
    vi modified;
    if (s[i] == 0) {
      if (!roll(i, 0, da, modified)) {
        ok = false;
        break;
      }
    } else {
      if (!roll(i, 1, db, modified)) {
        ok = false;
        break;
      }
    }
  }

  if (ok) ok = backtrack(n - 1);

  if (!ok) {
    printf("NO\n");
  } else {
    printf("%d", s[0]);
    for (int i = 1; i < n; ++i) printf(" %d", s[i]);
    printf("\n");
  }
}


