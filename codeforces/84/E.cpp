#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e0 = 1, e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

const l dx[] = {0, 0, 1, -1};
const l dy[] = {-1, 1, 0, 0};

struct point { l x, y; };

const l Z = 26;
const l MAX = 50;

point start, finish;
l n, m, k;
l around_start, around_finish;
l shortest;
string answer;
l D[MAX][MAX];
vector<string> M;

bool fit(l x, l y) {
  return (x >= 0) and (x < n) and (y >= 0) and (y < m);
}

l to_bit(char c) { return e0 << (c - 'a'); }

void check(l mask) {
  if ((mask & around_finish) == 0) return;
  fill(&D[0][0], &D[MAX][0], 0);
  queue<point> q;
  q.emplace(finish);
  D[finish.x][finish.y] = 1;
  while (not q.empty()) {
    auto u = q.front(); q.pop();
    l r = D[u.x][u.y];
    if (r > shortest) return;
    for (l d = 0; d < 4; d++) {
      l x = u.x + dx[d], y = u.y + dy[d];
      if ((not fit(x, y)) or D[x][y] != 0) continue;
      if (M[x][y] == 'S') {
        string candidate = "";
        vector<point> wave; wave.push_back({x, y});
        for (l i = r; i > 1; i--) {
          vector<point> next;
          char c = 'z' + 1;
          for (const auto p : wave) {
            for (l j = 0; j < 4; j++) {
              l a = p.x + dx[j], b = p.y + dy[j];
              if ((not fit(a, b)) or (D[a][b] != i)) continue;
              D[a][b] = -1;
              if (M[a][b] < c) {
                next.clear();
                c = M[a][b];
              }
              if (M[a][b] == c) next.push_back({a, b});
            }
          }
          candidate += c;
          swap(next, wave);
        }
        if (r < shortest) {
          answer = candidate;
          shortest = r;
        } else if (candidate < answer) {
          answer = candidate;
        }
        return;
      }
      if (mask & to_bit(M[x][y])) {
        D[x][y] = r + 1;
        q.push({x, y});
      } else {
        D[x][y] = -1;
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  while (cin >> n >> m >> k) {
    shortest = INF;
    M.resize(n);
    for (l i = 0; i < n; i++) cin >> M[i];
    l mask = 0;
    for (l i = 0; i < n; i++) {
      for (l j = 0; j < m; j++) {
        if (M[i][j] == 'S') { start = {i, j}; continue; }
        if (M[i][j] == 'T') { finish = {i, j}; continue; }
        mask = mask | to_bit(M[i][j]);
      }
    }
    // LOG << "letters = " << bitset<MAX>(mask) << '\n';
    // LOG << start.x << ' ' << start.y << '\n';
    // LOG << finish.x << ' ' << finish.y << '\n';
    around_start = 0;
    for (l d = 0; d < 4; d++) {
      if (fit(start.x + dx[d], start.y + dy[d])) {
        if (M[start.x + dx[d]][start.y + dy[d]] == 'T') {
          shortest = 0;
          break;
        }
        around_start = around_start | to_bit(M[start.x + dx[d]][start.y + dy[d]]);
      }
    }
    if (shortest == 0) {
      cout << '\n';
      continue;
    }
    around_finish = 0;
    for (l d = 0; d < 4; d++) {
      if (fit(finish.x + dx[d], finish.y + dy[d]))
        around_finish = around_finish | to_bit(M[finish.x + dx[d]][finish.y + dy[d]]);
    }
    for (l a = 0; a < Z; a++) {
      if ((around_start & (e0 << a)) == 0) continue;
      check(e0 << a);
      if (k == 1) continue;
      for (l b = 0; b < Z; b++) {
        if ((b == a) or ((mask & (e0 << b)) == 0)) continue;
        check((e0 << a) | (e0 << b));
        if (k == 2) continue;
        for (l c = b + 1; c < Z; c++) {
          if ((c == a) or ((mask & (e0 << c)) == 0)) continue;
          check((e0 << a) | (e0 << b) | (e0 << c));
          if (k == 3) continue;
          for (l d = c + 1; d < Z; d++) {
            if ((d == a) or ((mask & (e0 << d)) == 0)) continue;
            check((e0 << a) | (e0 << b) | (e0 << c) | (e0 << d));
          }
        }
      }
    }
    if (shortest == INF) {
      cout << "-1\n";
    } else {
      cout << answer << '\n';
    }
    // break;
  }
}
