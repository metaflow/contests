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
  int n; cin >> n;
  vi digits(60, 0);
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    reverse(s.begin(), s.end());
    for (int j = 0; j < s.size(); j++) {
      digits[j] += s[j] - '0';
    }
  }
  for (int i = 0; i < digits.size() - 1; i++) {
    digits[i + 1] += digits[i] / 10;
    digits[i] %= 10;
  }
  int i = digits.size() - 1;
  while (i > 0 && digits[i] == 0) i--;
  ll r = 0;
  for (int j = 0; j < 10 && i >= 0; j++) {
    r *= 10;
    r += digits[i];
    i--;
  }
  cout << r << endl;
}
