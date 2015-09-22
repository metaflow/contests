// time 23:00
#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

struct element {
  l value;
  l target, start;
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    vl columns(n);
    for (l i = 0; i < n; i++) cin >> columns[i];
    vl v;
    vii to_xy;
    for (l i = 0; i < n; i++) {
      for (l j = 0; j < columns[i]; j++) {
        l t; cin >> t;
        v.emplace_back(t);
        to_xy.emplace_back(i + 1, j + 1);
      }
    }
    vector<ii> solution;
    for (l i = 0; i < v.size(); i++) {
      while (v[i] - 1 != i) {
        solution.emplace_back(i, v[i] - 1);
        swap(v[i], v[v[i] - 1]);
      }
    }
    cout << solution.size() << endl;
    for (auto s : solution) {
      cout << to_xy[s.first].first << " " << to_xy[s.first].second << " "
           << to_xy[s.second].first << " " << to_xy[s.second].second << endl;
    }
  }
}
