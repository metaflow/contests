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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

void srt(string& s, int f, int t) {
  if ((t - f) % 2 == 1) return;
  int m = (f + t) / 2;
  srt(s, f, m);
  srt(s, m, t);
  for (ll i = 0; i < (m - f); i++) {
    if (s[f + i] == s[m + i]) continue;
    if (s[f + i] < s[m + i]) break;
    for (ll j = 0; j < (m - f); j++) {
      swap(s[f + j], s[m + j]);
    }
    break;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string a;
  string b;
  while (cin >> a >> b) {
    srt(a, 0, a.size());
    srt(b, 0, b.size());
    if (a == b) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
