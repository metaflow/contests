#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  string s;
  while (cin >> s) {
    int v = 0;
    int c = 0;
    bool ok = true;
    for (int i = 0; i < s.size(); i++) {
      switch (s[i]) {
        case '(' : v++; break;
        case ')' : v--; break;
        case '#' : v--; c++; break;
      }
      if (v < 0) ok = false;
    }
    if (ok) {
      // checking solution
      int b = 0; int t = c;
      for (int i = 0; i < s.size(); i++) {
        switch (s[i]) {
          case '(' : b++; break;
          case ')' : b--; break;
          case '#' : t--; b--; if (t == 0) b -= v; break;
        }
        if (b < 0) ok = false;
      }
      if (b != 0) ok = false;
    }
    if (ok) {
      for (int i = 0; i < c - 1; i++) {
        cout << "1" << endl;
      }
      cout << v + 1 << endl;
    } else {
      cout << -1 << endl;
    }
  }
}
