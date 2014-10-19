#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n, d1, d2, l;
  while (cin >> n >> l >> d1 >> d2) {
    vector<int> v(n);
    vector<ii> p;
    for (int i = 0; i < n; i++) cin >> v[i];
    for (int i = 0; i < n; i++) {
      p.emplace_back(v[i], 0);
      if (v[i] - d1 >= 0) p.emplace_back(v[i] - d1, 1);
      if (v[i] + d1 <= l) p.emplace_back(v[i] + d1, 1);
      if (v[i] - d2 >= 0) p.emplace_back(v[i] - d2, 2);
      if (v[i] + d2 <= l) p.emplace_back(v[i] + d2, 2);
    }
    p.emplace_back(l + 1, 0);
    sort(p.begin(), p.end());
    int o = -1;
    bool has[3];
    int a1 = -1, a2 = -1;
    for (auto pp : p) {
      int x = pp.first;
      int j = pp.second;
      if (x != o) {
        if (o != -1) {
          if (has[1]) {
            if (has[0]) a1 = INF;
            if (a1 == -1) a1 = o;
          }
          if (has[2]) {
            if (has[0]) a2 = INF;
            if (a2 == -1) a2 = o;
          }
          if (has[1] && has[2] && a1 != INF && a2 != INF) a1 = a2 = o;
        }
        o = x;
        for (int i = 0; i < 3; i++) has[i] = false;
      }
      has[j] = true;
    }
    vi add;
    if (a1 != INF) add.emplace_back(a1);
    if (a2 != INF && a2 != a1) add.emplace_back(a2);
    cout << add.size() << endl;
    if (!add.empty()) {
      for (int i = 0; i < add.size(); i++) {
        if (i) cout << " ";
        cout << add[i];
      }
      cout << endl;
    }
  }
}
