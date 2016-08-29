#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

default_random_engine source(random_device{}());

void print_case() {
  vi v;
  uniform_int_distribution<> s(0, 1);
  for (int i = 1; i <= 8; i++) {
    v.emplace_back(i * (1 - 2 * s(source)));
  }
  for (int i = 0; i < 8; i++) {
    uniform_int_distribution<> p(i, 7);
    swap(v[i], v[p(source)]);
  }
  for (int i = 0; i < 8; i++) {
    if (i) printf(" ");
    printf("%d", v[i]);
  }
  printf("\n");
}

int main() {
  int cases = 20;
  for (int i = 0; i < cases; i++) {
    print_case();
  }
  printf("0\n");
}
