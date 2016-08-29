#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 77;

int main() {
  ll a[MAX];
  a[0] = 1; a[1] = 1; a[2] = 2;
  for (int i = 3; i < MAX; i++) a[i] = a[i - 2] + a[i - 3];
  int n;
  while (cin >> n) cout << a[n] << endl;
}
