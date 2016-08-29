#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  cin.sync_with_stdio(false);
  string number;
  int base_from, base_to;
  while (cin >> number) {
    cin >> base_from >> base_to;
    int a = 0;
    for (char c : number) {
      a *= base_from;
      if (c >= '0' && c <= '9') {
        a += c - '0';
      } else {
        a += c - 'A' + 10;
      }
    }

    int p = 6;
    char buffer[8] = "       ";
    //buffer[7] = 0;
    for (p = 6; p >= 0; p--) {
      int r = a % base_to;
      a /= base_to;
      if (r < 10) {
        buffer[p] = '0' + r;
      } else {
        buffer[p] = 'A' + (r - 10);
      }
      if (a == 0) break;
    }
    if (a > 0) {
      printf("  ERROR\n");
    } else {
      printf("%s\n", buffer);
    }
  }
}
