#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 100000;
int RMQ[4 * MAX];
int bears[MAX];

// [a, b]
void build_rmq(int p, int a, int b) {
  if (a == b) {
    RMQ[p] = bears[a];
    return;
  }
  int m = (a + b) / 2;
  build_rmq(2 * p, a, m);
  build_rmq(2 * p + 1, m + 1, b)
  int pa = RMQ[2 * p];
  int pb = RMQ[2 * p + 1];
  if (bears[pa] < bears[pb]) {
    RMQ[p] = pa;
  } else {
    RMQ[p] = pb;
  }
}

int main() {
  int n;
  while (cin >> n) {
    for (int i = 0; i < n; i++) cin >> bears[i];
    build_rmq(1, 0, n - 1);
  }
}
