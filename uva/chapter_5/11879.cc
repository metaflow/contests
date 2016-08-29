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
  while (cin >> s, s != "0") {
    int r = 0;
    for (int i = 0; i < s.size(); i++) {
      r = (r * 10 + (s[i] - '0')) % 17;
    }
    if (r == 0) {
      cout << 1 << endl;
    } else {
      cout << 0 << endl;
    }
  }
}
