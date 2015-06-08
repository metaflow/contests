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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n; cin >> n;
    vi v(n);
    for (int i = 1; i <= n; i++) {
      vi t(n);
      for (int j = 0; j < i; j++) {
        cin >> t[j];
        int m = 0;
        if (j > 0) m = max(m, v[j - 1]);
        if (j < i - 1) m = max(m, v[j]);
        t[j] += m;
      }
      swap(t, v);
    }
    int answer = 0;
    for (auto i : v) answer = max(answer, i);
    cout << answer << endl;
  }
}
