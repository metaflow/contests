#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  char c;
  int n = 0;
  while (c = getchar(), c != EOF) {
    if (c >= '0' && c <= '9')  { n += (c - '0'); continue; }
    if (c == '!' || c == '\n') { printf("\n"); continue; }
    if (c == 'b') c = ' ';
    while (n--) printf("%c", c);
    n = 0;
  }
}
