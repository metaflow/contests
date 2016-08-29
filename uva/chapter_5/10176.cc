#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MOD = 131071;


int main() {
  string s;
  int a = 0;
  while (cin >> s) {
    for (auto c : s) {
      a <<= 1;
      a %= MOD;
      switch (c) {
        case '#':
          if (a == 0) {
            cout << "YES" << endl;
          } else {
            cout << "NO" << endl;
          }
          a = 0;
          break;
        case '1': a++; break;
      }
    }

  }
}
