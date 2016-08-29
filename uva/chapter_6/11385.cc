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
  while (tcc--) {
    int n;
    cin >> n;
    vi v;
    int m = 0;
    for (int i = 0; i < n; i++) {
      int a; cin >> a;
      v.emplace_back(a);
      m = max(m, a);
    }
    string s;
    getline(cin, s);
    getline(cin, s);
    vector<char> vc;
    for (char c : s) {
      if (c >= 'A' && c <= 'Z') vc.emplace_back(c);
    }
    int a = 0, b = 1;
    while (true) {
      int t = b;
      b += a;
      a = t;
      bool found = false;
      for (int i = 0; i < v.size(); i++) {
        if (v[i] == b) {
          found = true;
          printf("%c", vc[i]);
          break;
        }
      }
      if (b == m) break;
      if (!found) printf(" ");
    }
    printf("\n");
  }
}
