#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

struct node;
using pnode = shared_ptr<node>;
using graph = vector<pnode>;

struct node {
  vector<pnode> adjusted;
  int age;
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, m;
  while (cin >> n >> m) {
    graph g(n);
    for (ll i = 0; i < n; i++) g[i] = make_shared<node>();
    for (ll i = 0; i < m; i++) {
      ll a, b; cin >> a >> b;
      a--; b--;
      g[a]->adjusted.emplace_back(g[b]);
      g[b]->adjusted.emplace_back(g[a]);
    }
    ll answer = 0;
    ll ways = 0;
    if (m == 0) {
      answer = 3;
      ways = n * (n - 1) * (n - 2) / 6;
    } else {
      ll w1 = 0;
      bool cycle = false;
      for (auto u : g) {
        if (u->age != 0) continue;
        ll odd = 0, even = 0;
        queue<pnode> q;
        q.emplace(u);
        u->age = 1;
        // u->visited = true;
        while (!q.empty()) {
          auto p = q.front(); q.pop();
          if (p->age % 2 == 1) {
            odd++;
          } else {
            even++;
          }
          for (auto v : p->adjusted) {
            if (v->age != 0) {
              if (abs(v->age - p->age) % 2 == 0) {
                cycle = true;
              }
              continue;
            }
            v->age = p->age + 1;
            q.emplace(v);
          }
        }
        w1 += odd * (odd - 1) / 2 + even * (even - 1) / 2;
      }
      if (cycle) {
        answer = 0;
        ways = 1;
      } else if (w1 > 0) {
        answer = 1;
        ways = w1;
      } else {
        answer = 2;
        ways = m * (n - 2);
      }
    }
    cout << answer << " " << ways << endl;
  }
}
