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
    int counts[3] = {0};
    bool ok = true;
    string s;
    cin >> s;
    int state = 0;
    for (char c : s) {
      switch (c) {
        case 'M': ok = (state == 0); state++; break;
        case 'E': ok = (state == 1); state++; break;
        case '?': counts[state]++; break;
        default: ok = false; break;
      }
      if (!ok) break;
    }
    ok = ok && (state == 2)
            && (counts[0] > 0)
            && (counts[1] > 0)
            && (counts[2] == counts[0] + counts[1]);
    if (ok) {
      cout << "theorem" << endl;
    } else {
      cout << "no-theorem" << endl;
    }
  }
}
