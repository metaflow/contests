#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

default_random_engine source(random_device{}());

int random_in_range(int a, int b) {
  return uniform_int_distribution<>(a, b)(source);
}

const int MAX = 50; // note: according to problem MAX = 2000

int main() {
  int tcc = 10;
  printf("%d\n", tcc);
  for (int tc = 0; tc < tcc; tc++) {
    int trees = random_in_range(1, MAX);
    int max_height = random_in_range(1, 2000);
    int f = random_in_range(1, 500);
    printf("%d %d %d\n", trees, max_height, f);
    for (int t = 0; t < trees; t++) {
      vi h;
      h.resize(random_in_range(0, MAX));
      printf("%lu", h.size());
      for (auto &x : h) x = random_in_range(1, max_height);
      sort(h.begin(), h.end());
      for (auto x : h) printf(" %d", x);
      printf("\n");
    }
  }
  printf("0\n");
}
