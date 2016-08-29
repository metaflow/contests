#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  string s;
  getline(cin, s);
  while (getline(cin, s), s[1] != '_') {
    int c = 0, p = 1;
    for (int i = 0; i < 5; i++) {
      c <<= 1;
      if (s[p] == 'o') c++;
      p++;
    }
    p++;
    for (int i = 0; i < 3; i++) {
      c <<= 1;
      if (s[p] == 'o') c++;
      p++;
    }
    printf("%c", (char) c);
  }
  // printf("\n");
}
