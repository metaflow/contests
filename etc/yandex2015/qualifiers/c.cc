#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
using vllu = vector<llu>;
const int INF = numeric_limits<int>::max();
using ie = pair<llu, int>;

int main() {
  ios_base::sync_with_stdio(false);
  int N;
  cin >> N;
  vllu a(N);
  for (int i = 0; i < N; i++) cin >> a[i];
  int D;
  cin >> D;
  vector<vi> docs(D);
  vector<ie> index;
  for (int i = 0; i < D; i++) {
    docs[i].resize(N);
    for (int j = 0; j < N; j++) {
      cin >> docs[i][j];
    }
    ie e;
    e.first = 0;
    e.second = i;
    for (int j = 0; j < N; j++) {
      e.first -= a[j] * docs[i][j];
    }
    index.emplace_back(e);
  }
  sort(index.begin(), index.end());
  list<ie> il;
  for (auto e : index) il.emplace_back(e);
  index.resize(0);
  int q;
  cin >> q;
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int k; cin >> k;
      auto it = il.begin();
      while (k--) {
        if (it != il.begin()) printf(" ");
        printf("%d", it->second + 1);
        it++;
      }
      printf("\n");
    } else {
      llu d, i, v;
      cin >> d >> i >> v; i--; d--;
      // get current
      ie c;
      c.second = d;
      for (int j = 0; j < N; j++) {
        c.first -= a[j] * docs[d][j];
      }
      // remove
      auto it = lower_bound(il.begin(), il.end(), c);
      il.erase(it);
      // update
      c.first += a[i] * docs[d][i];
      docs[d][i] = v;
      c.first -= a[i] * docs[d][i];
      // insert
      it = lower_bound(il.begin(), il.end(), c);
      il.insert(it, c);
    }
  }
}
