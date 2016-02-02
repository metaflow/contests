#include<bits/stdc++.h>
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

const l MAX = 5001;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    l m = 0;
    vl vs(MAX);
    for (l i = 0; i < n; i++) {
      l a; cin >> a; vs[a]++;
      m = max(m, a);
    }
    vl answer;
    for (l i = 0; i <= m; i++) {
      if (!vs[i]) continue;
      vs[i]--;
      answer.push_back(i);
    }
    for (l i = m - 1; i > 0; i--) if (vs[i]) answer.push_back(i);
    reverse(answer.begin(), answer.end());
    cout << answer.size() << endl;
    bool first = true;
    for (auto i : answer) {
      if (!first) cout << " ";
      first = false;
      cout << i;
    }
    cout << endl;
  }
}
