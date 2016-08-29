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

bool random_bool() {
  return random_in_range(0, 1) == 0;
}

const int MAX = 100;

int main() {
  int cases = 20;
  for (int i = 0; i < cases; i++) {
    int n = random_in_range(2, 30);
    for (int j = 0; j < n; j++) {
      if (j) printf(" %c ", random_bool() ? '+' : '-');
      printf("%d", random_in_range(0, 99));
    }
    printf("\n");
  }
}
