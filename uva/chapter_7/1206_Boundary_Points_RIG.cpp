#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  default_random_engine source(random_device{}());
  uniform_real_distribution<double> coordinate(-100000, 100000);
  uniform_int_distribution<> count(1, 100);
  for (int i = 0; i < 5; i++) {
    int n = count(source);
    for (int j = 0; j < n; j++) {
      if (j != 0) printf(" ");
      printf("(%.3f,%.3f)", coordinate(source), coordinate(source));
    }
    printf("\n");
  }
}
