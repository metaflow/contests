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
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n, k; cin >> n >> k;
    string s; cin >> s;
    ll v = 1; int length = 0;
    ll answer = 0;
    for (int i = 0; i < n; i++) {
      int a = s[i] - '0';
      if (a == 0) {
        length = 0;
        v = 1;
        continue;
      }
      v *= a;
      length++;
      if (length > k) {
        length--;
        v /= (s[i - k] - '0');
      }
      if (length == k) answer = max(answer, v);
    }
    cout << answer << endl;
  }
}
