#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 301;

int main() {
  int n;
  while (cin >> n) {
    vi v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    bool m[MAX][MAX];
    fill(&m[0][0], &m[MAX][0], false);
    for (int i = 0; i < n; i++) {
      string s;
      cin >> s;
      for (int j = 0; j < n; j++) m[i][j] = (s[j] == '1');
    }
    for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      m[i][j] = m[i][j] || (m[i][k] && m[k][j]);
    }
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (m[i][j] && v[i] > v[j]) swap(v[i], v[j]);
      }
    }
    for (int i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << v[i];
    }
    cout << endl;
  }
}
