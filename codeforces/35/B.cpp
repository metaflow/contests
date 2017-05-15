#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
const bool enable_log = true;
#else
const bool enable_log = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ifstream fin("input.txt"); cin.rdbuf(fin.rdbuf());
  ofstream fout("output.txt"); cout.rdbuf(fout.rdbuf());
  l n, m, r;
  while (cin >> n >> m >> r) {
    vvb occupied(n, vb(m));
    unordered_map<string, ll> positions;
    F(i, 0, r) {
      string op;
      cin >> op;
      if (op == "+1") {
        l x, y; string name;
        cin >> x >> y >> name;
        x--; y--;
        while (x < n and occupied[x][y]) {
          y++;
          if (y >= m) {
            y = 0;
            x++;
          }
        }
        if (x < n) {
          positions[name] = make_pair(x, y);
          occupied[x][y] = true;
        }
      } else {
        string name; cin >> name;
        if (positions.count(name)) {
          auto p = positions[name];
          cout << p.first + 1 << ' '
               << p.second + 1 << lf;
          positions.erase(name);
          occupied[p.first][p.second] = false;
        } else {
          cout << "-1 -1\n";
        }
      }
    }
  }
}
