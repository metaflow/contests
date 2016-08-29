#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int tcc;
  cin >> tcc;
  string s; getline(cin, s);
  while (tcc--) {
    getline(cin, s);
    stack<char> p;
    bool ok = true;
    for (auto c : s) {
      switch (c) {
        case '(':
        case '[': p.push(c); break;
        case ')':
          if (p.empty() || p.top() != '(') { ok = false; } else { p.pop(); }
          break;
        case ']':
          if (p.empty() || p.top() != '[') { ok = false; } else { p.pop(); }
          break;
      }
      if (!ok) break;
    }
    ok = ok && p.empty();
    if (ok) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
}
