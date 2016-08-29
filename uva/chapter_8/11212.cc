#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

// move
ll edit(ll n, int a, int b, int k, int m) {
  ll r = 0;
  int t = 0;
  int p = 0;
  if (k >= a) k++;
  ll mult = 1;
  ll q = n;
  while (t < m) {
    if (t == k) {
      ll cut = n;
      int i = 0;
      for (; i < a; i++) cut /= 10;
      for (; i < b; i++) {
        r += mult * (cut % 10);
        mult *= 10;
        cut /= 10;
        t++;
      }
      continue;
    }
    if (p >= a && p < b) { q /= 10; p++; continue; }
    r += mult * (q % 10);
    mult *= 10;
    q /= 10;
    p++;
    t++;
  }
  return r;
}

unordered_map<ll, int> dist;

void fill_targets() {
  ll n = 1;
  for (int m = 2; m < 10; m++) {
    n = n * 10 + m;
    queue<ll> q;
    q.emplace(n);
    dist[n] = 0;
    int max_distance = 0;
    int d = 1;
    while (!q.empty()) {
      ll x = q.front(); q.pop();
      if (x < 1) { d = -x; continue; }
      for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
          for (int k = 0; k < m - (j - i); k++) {
            auto t = edit(x, i, j, k, m);
            if (dist.count(t)) continue;
            dist[t] = d;
            if (d + 1 > max_distance) {
              max_distance = d + 1;
              q.emplace(-max_distance);
            }
            if (max_distance < 3) q.emplace(t);
          }
        }
      }
    }
  }
}

int find_distance(int n, int m) {
  if (dist.count(n)) return dist[n];
  queue<ll> q;
  q.emplace(n);
  int max_distance = 0;
  int d = 1;
  while (!q.empty()) {
    ll x = q.front(); q.pop();
    if (x < 1) { d = -x; continue; }
    for (int i = 0; i < m; i++) {
      for (int j = i + 1; j < m; j++) {
        for (int k = 0; k < m - (j - i); k++) {
          auto t = edit(x, i, j, k, m);
          if (dist.count(t)) {
            return dist[t] + d;
          }
          if (d + 1 > max_distance) {
            max_distance = d + 1;
            q.emplace(-max_distance);
          }
          if (max_distance < 3) q.emplace(t);
        }
      }
    }
  }
  return 5;
}

int main() {
  fill_targets();
  int m;
  int tc = 0;
  while (cin >> m, m) {
    ll n = 0;
    for (int i = 0; i < m; i++) {
      int x; cin >> x;
      n = n * 10 + x;
    }
    tc++;
    printf("Case %d: %d\n", tc, find_distance(n, m));
  }
  return 0;
}
