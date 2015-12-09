#include<vector>
#include<algorithm>
#include<iostream>
#include<tuple>
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
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

struct edge {
  l weight;
  l not_taken;
  l index;
  l from, to;
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m;
  while (cin >> n >> m) {
    vector<edge> edges(m);
    for (l i = 0; i < m; i++) {
      l w, t;
      cin >> edges[i].weight >> t;
      edges[i].not_taken = 1 - t;
      edges[i].index = i;
    }
    sort(edges.begin(), edges.end(), [](const edge& a, const edge& b) {
      return tie(a.weight, a.not_taken, a.index) <
             tie(b.weight, b.not_taken, b.index);
    });
    vl max_adj(n); // max index of node connected with
    l mst_size = 1;
    l d = 0; // where to insert big edge to existing graph
    bool possible = true;
    for (auto& e : edges) {
      if (e.not_taken == 0) { // == taken
        mst_size++;
        max_adj[0] = mst_size - 1;
        max_adj[mst_size - 1] = mst_size - 1;
        d = 1;
        e.from = 0;
        e.to = mst_size - 1;
        continue;
      }
      while (d < mst_size && max_adj[d] == mst_size - 1) d++;
      if (d == mst_size) {
        possible = false;
        break;
      }
      e.from = d;
      max_adj[d]++;
      e.to = max_adj[d];
    }
    possible = possible && (mst_size == n);
    if (possible) {
      sort(edges.begin(), edges.end(), [] (const edge& a, const edge& b) {
        return a.index < b.index;
      });
      for (auto e : edges) {
        cout << e.from + 1 << " " << e.to + 1 << endl;
      }
    } else {
      cout << -1 << endl;
    }
  }
}
