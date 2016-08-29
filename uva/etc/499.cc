#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();


int main() {
  cout.sync_with_stdio(false);
  string s;
  while (getline(cin, s)) {
    vi lowercase(26), uppercase(26);
    int m = 0;
    for (char c : s) {
      if (c >= 'a' && c <= 'z') m = max(m, ++lowercase[c - 'a']);
      if (c >= 'A' && c <= 'Z') m = max(m, ++uppercase[c - 'A']);
    }
    for (size_t i = 0; i < uppercase.size(); i++) {
      if (uppercase[i] != m) continue;
      cout << (char)('A' + i);
    }
    for (size_t i = 0; i < lowercase.size(); i++) {
      if (lowercase[i] != m) continue;
      cout << (char)('a' + i);
    }
    cout << ' ' << m << endl;
  }
}
