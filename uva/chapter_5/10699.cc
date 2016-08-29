#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 1000001;

int c[MAX];

void sieve() {
  fill_n(c, MAX, 0);
  for (int i = 2; i < MAX; i++) {
    if (c[i]) continue;
    for (int j = i; j < MAX; j += i) c[j]++;
  }
}

int main() {
  sieve();
  int n;
  while (cin >> n, n) {
    printf("%d : %d\n", n, c[n]);
  }
}
