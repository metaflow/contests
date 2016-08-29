#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  default_random_engine rng(random_device{}());
  uniform_int_distribution<> dist(1, 9999);
  int N = 1000;
  printf("%d\n", N);
  for (int i = 0; i < N; i++) {
    printf("%d\n", dist(rng));
  }
}
