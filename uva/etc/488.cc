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
    int h, f;
    cin >> h >> f;
    while (f--) {
      for (int i = 1; i < h; i++) {
        for (int j = 0; j < i; j++) cout << i;
        cout << endl;
      }
      for (int i = h; i > 0; i--) {
        for (int j = 0; j < i; j++) cout << i;
        cout << endl;
      }
      if (f) cout << endl;
    }
    if (tcc) cout << endl;
  }
}
