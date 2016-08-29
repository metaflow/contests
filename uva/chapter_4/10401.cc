#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 16;

ll memo[MAX][MAX];
int pos[MAX];

ll count(int at, int right, int n) {
  if (at < 0) return 1;
  auto &r = memo[at][right];
  if (r == -1) {
    r = 0;
    if (pos[at] == 0)  {
      for (int i = 1; i <= n; i++) {
        if (right == 0 || abs(i - right) >= 2) {
          r += count(at - 1, i, n);
        }
      }
    } else {
      if (right == 0 || abs(pos[at] - right) >= 2) {
        r = count(at - 1, pos[at], n);
      }
    }
  }
  return r;
}

int main() {
  string s;
  while (cin >> s) {
    fill(&memo[0][0], &memo[MAX][0], -1);
    for (int i = 0; i < s.size(); i++) {
      char &c = s[i];
      if (c == '?') { pos[i] = 0; continue; }
      if (c >= 'A' && c <= 'F') { pos[i] = 10 + (c - 'A'); continue; };
      pos[i] = c - '0';
    }
    cout << count(s.size() - 1, 0, s.size())  << endl;
  }
}
