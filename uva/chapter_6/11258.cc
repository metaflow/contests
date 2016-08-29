#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 210;

ll memo[MAX];
string s;

ll dp(int p) {
  if (p == s.size()) return 0;
  ll &r = memo[p];
  if (r == -1) {
    if (s[p] == '0') {
      r = dp(p + 1);
    } else {
      for (int i = 1; (i < 11) && (i + p <= s.size()); i++) {
        ll a = atol(s.substr(p, i).c_str());
        if (a > numeric_limits<int>::max()) break;
        r = max(r, a + dp(p + i));
      }
    }
  }
  return r;
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    cin >> s;
    fill_n(memo, MAX, -1);
    cout << dp(0) << endl;
  }
}
