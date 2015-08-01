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
  string s;
  cin >> s;
  reverse(s.begin(), s.end());
  vvi suffix(s.size());
  vvi positions(26);
  for (int i = s.size() - 1; i >= 0; i--) {
    if (i + 1 < s.size()) {
      suffix[i] = suffix[i + 1];
    } else {
      suffix[i].resize(26);
    }
    suffix[i][s[i] - 'a']++;
    positions[s[i] - 'a'].emplace_back(i);
  }
  for (int i = 0; i < 26; i++) {
    reverse(positions[i].begin(), positions[i].end());
  }
  vi left(26);
  for (int i = 0; i < 26; i++) {
    left[i] = suffix[0][i] / 2;
  }
  int pos = 0; // [pos, s.size())
  string result = "";
  for (int i = 0; i < s.size() / 2; i++) {
    for (int j = 0; j < 26; j++) {
      if (left[j] == 0) continue;
      auto a = lower_bound(positions[j].begin(), positions[j].end(), pos);
      if (a == positions[j].end()) continue;
      // check if it's enough characters
      bool ok = true;
      for (int k = 0; k < 26; k++) {
        if (left[k] > suffix[*a][k]) {
          ok = false;
          break;
        }
      }
      if (ok) {
        left[j]--;
        result += char(j + 'a');
        pos = *a + 1;
        break;
      }
    }
  }
  cout << result << endl;
}
