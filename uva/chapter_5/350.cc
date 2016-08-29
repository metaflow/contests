#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int m, z, l, i;

int f(int a) {
  return (a * z + i) % m;
}

int main() {
  int tc = 0;
  while (cin >> z >> i >> m >> l, z && i && m && l) {
    tc++;
    int r = l;
    int t = l;
    while (true) {
      r = f(r);
      t = f(f(t));
      if (r == t) break;
    }
    int length = 1;
    t = f(r);
    while (t != r) { t = f(t); length++; }
    printf("Case %d: %d\n", tc, length);
  }
}
