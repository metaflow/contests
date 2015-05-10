#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int T[5][5] =
    {
        {0,0,0,0,0},
        {0,1,2,3,4},
        {0,2,-1,4,-3},
        {0,3,-4,-1,2},
        {0,4,3,-2,-1},
    };

int main() {
  int tcc;
  cin >> tcc;
  // correct way is to manage "all possible so far", calculate state for one string and deduct if it's possible to get to i -> k -> -1
  for (int tc = 1; tc <= tcc; tc++) {
    llu n, x; cin >> n >> x;
    string s;
    cin >> s;
    int t = 1;
    int p = 1;
    char state = '_';
    for (llu i = 0; i < x; i++) {
      for (llu j = 0; j < n; j++) {
        int c = 1;
        switch (s[j]) {
          case 'i': c = 2; break;
          case 'j': c = 3; break;
          case 'k': c = 4; break;
        }
        t = T[t][c];
        if (t < 0) { p = -p; t = -t; }
        if (t == 2 && p == 1 && state == '_') state = 'i';
        if (t == 4 && p == 1 && state == 'i') state = 'k';
      }
    }
    if (state == 'k' && t == 1 && p == -1) {
      printf("Case #%d: YES\n", tc);
    } else {
      printf("Case #%d: NO\n", tc);
    }
  }
}
