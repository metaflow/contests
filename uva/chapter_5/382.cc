#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  printf("PERFECTION OUTPUT\n");
  int n;
  while (cin >> n, n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
      if (n % i == 0) {
        sum += i;
      }
    }
    printf("%5d  ", n);
    if (n < sum) {
      printf("ABUNDANT\n");
    } else if (n == sum) {
      printf("PERFECT\n");
    } else {
      printf("DEFICIENT\n");
    }
  }
//    15  DEFICIENT
//    28  PERFECT
//     6  PERFECT
//    56  ABUNDANT
// 60000  ABUNDANT
//    22  DEFICIENT
//   496  PERFECT"
  printf("END OF OUTPUT\n");
}
