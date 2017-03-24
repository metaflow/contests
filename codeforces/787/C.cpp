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
const l e0=1, e3=1000, e5=100000, e6=e3*e3, e7=10*e6, e8=10*e7, e9=10*e8;
#define ALL(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

l n;
l game(l who, l monster, vvl& state, vvl& v) {
  l& s = state[who][monster];
  if (not s) {
    s = 1;
    bool loops = false;
    for (auto j : v[who]) {
      l p = (monster + 2 + j - 1) % n + 1;
      if (p == 1) {
        s = 2;
        return s;
      }
      l other = game(1 - who, p - 2, state, v);
      if (other == 3) {
        s = 2;
        return s;
      }
      if (other == 1) loops = true;
    }
    if (not loops) s = 3;
  }
  return s;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  while (cin >> n) {
    l m; vvl v(2);
    cin >> m;
    v[0].resize(m);
    F(i, 0, m) cin >> v[0][i];
    cin >> m;
    v[1].resize(m);
    F(i, 0, m) cin >> v[1][i];
    vvl state(2, vl(n, 1)); // 0 unknown, 1 - loop, 2 - win, 3 - loose
    queue<ll> q;
    vvb in_queue(2, vb(n));
    for (l i : v[0]) {
      l p = n - i;
      state[0][p] = 2;
      for (l j : v[1]) {
        l t = (p - j + n) % n;
        if (not in_queue[1][t]) {
          q.emplace(1, t);
          in_queue[1][t] = true;
        }
      }
    }
    for (l i : v[1]) {
      l p = n - i;
      state[1][p] = 2;
      for (l j : v[0]) {
        l t = (p - j + n) % n;
        if (not in_queue[0][t]) {
          q.emplace(0, t);
          in_queue[0][t] = true;
        }
      }
    }
    state[0][0] = 3;
    state[1][0] = 3;
    while (not q.empty()) {
      l who, p; tie(who, p) = q.front(); q.pop();
      if (state[who][p] != 1) continue;
      l other = 1 - who;
      in_queue[who][p] = false;
      l looses = 0, wins = 0;
      for (l i : v[who]) {
        switch (state[other][(p + i) % n]) {
        case 2: looses++; break;
        case 3: wins++; break;
        }
      }
      if (looses == v[who].size()) {
        state[who][p] = 3;
      }
      if (wins) {
        state[who][p] = 2;
      }
      if (state[who][p] != 1) {
        for (l j : v[other]) {
          l t = (p - j + n) % n;
          if (state[other][t] == 1 and not in_queue[other][t]) {
            in_queue[other][t] = true;
            q.emplace(other, t);
          }
        }
      }
    }
    F(i, 0, n - 1) {
      if (i) cout << ' ';
      switch(state[0][i + 1]) {
      case 1: cout << "Loop"; break;
      case 2: cout << "Win"; break;
      case 3: cout << "Lose"; break;
      }
    }
    cout << '\n';
    F(i, 0, n - 1) {
      if (i) cout << ' ';
      switch(state[1][i + 1]) {
      case 1: cout << "Loop"; break;
      case 2: cout << "Win"; break;
      case 3: cout << "Lose"; break;
      }
    }
    cout << '\n';
  }
}
