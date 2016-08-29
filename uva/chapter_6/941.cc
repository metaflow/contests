#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

ll factorial(ll a) {
  if (a < 2) return 1;
  return a * factorial(a - 1);
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    string s;
    ll n;
    cin >> s >> n;
    vi count(26);
    ll sum = 0;
    for (auto c : s) {
      count[c - 'a']++;
      sum++;
    }
    ll a = factorial(sum);
    for (auto i : count) a /= factorial(i);
    string answer;
    while (sum > 0) {
      for (int i = 0; i < 26; i++) {
        if (!count[i]) continue;
        ll t = (a * count[i]) / sum;
        if (t > n) {
          answer += 'a' + (char)i;
          a = (a * count[i]) / sum;
          count[i]--;
          break;
        }
        n -= t;
      }
      sum--;
    }
    cout << answer << endl;
  }
}
