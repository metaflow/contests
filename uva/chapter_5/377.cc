#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int get_number() {
  string s;
  cin >> s;
  int i = 0;
  for (auto c : s) {
    i *= 4;
    switch (c) {
      case 'V': i += 0; break;
      case 'U': i += 1; break;
      case 'C': i += 2; break;
      case 'D': i += 3; break;
    }
  }
  return i;
}

int main() {
  int tcc;
  cin >> tcc;
  printf("COWCULATIONS OUTPUT\n");
  while (tcc--) {
    int a = get_number();
    int b = get_number();
    for (int i = 0; i < 3; i++) {
      char c;
      cin >> c;
      switch (c) {
        case 'A' : b += a; break;
        case 'L': b *= 4; break;
        case 'R': b /= 4; break;
      }
    }
    if (get_number() == b) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
  printf("END OF OUTPUT\n");
}
