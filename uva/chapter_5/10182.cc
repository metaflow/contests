#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int f(int k) {
  return 1 + 3 * (k + 1) * k;
}

int dx[] = {0, -1, -1, 0, +1, +1};
int dy[] = {-1, 0, +1, +1, 0, -1};

int main() {
  int n;
  while (cin >> n) {
    int k = floor(pow(n / 3, 0.5));
    while (f(k) < n) k++;
    int t = f(k);
    int x = k; int y = 0;
    int p = 0;
    while (t != n) {
      for (int i = 0; i < k && t != n; i++) {
        x += dx[p];
        y += dy[p];
        t--;
      }
      p++;
    }
    cout << x << " " << y << endl;
  }
}
