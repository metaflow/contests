#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int rand_range(int from, int to) {
  return from + rand() % (to - from + 1);
}

void print_case(int c, int r, int o, int d) {
  if (c + r + o == 0) return;
  printf("%d %d %d\n", c, r, o);
  for (int i = 0; i < c + r + o; i++) {
    printf("%d %d\n", rand_range(-d, d), rand_range(-d, d));
  }
}

int main() {
  srand (time(NULL));
  // small cases
  for (int i = 0; i < 3; i++) {
    print_case(
      rand_range(0, 5),
      rand_range(0, 5),
      rand_range(0, 5),
      10);
  }
  // mid cases
  for (int i = 0; i < 3; i++) {
    print_case(
      rand_range(0, 200),
      rand_range(0, 200),
      rand_range(0, 200),
      500);
  }
  // max cases
  for (int i = 0; i < 3; i++) {
    print_case(
      200,
      200,
      200,
      500);
  }
  printf("0 0 0\n");
  return 0;
}
