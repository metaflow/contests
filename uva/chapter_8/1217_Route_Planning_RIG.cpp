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

const int MAX = 100;

int main() {
  int roads = 10;
  int max_length = 20;
  printf("%d %d\n", MAX, roads);
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      if (j) printf(" ");
      if (i == j) {
        printf("0");
      } else {
        printf("%d", random_in_range(0, 10));
      }
    }
    printf("\n");
  }
  int p[MAX];
  for (int i = 0; i < MAX; i++) p[i] = i + 1;
  for (int i = 0; i < roads; i++) {
    for (int j = 0; j < MAX; j++) {
      swap(p[j], p[random_in_range(j, MAX - 1)]);
    }
    int l = random_in_range(2, max_length);
    for (int j = 0; j < l; j++) {
      if (j) printf(" ");
      printf("%d", p[j]);
    }
    printf("\n");
  }
}
