#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  stack<char> s;
  char c;
  while (c = getchar(), c != EOF) {
    if (isspace(c)) {
      while (!s.empty()) { printf("%c", s.top()); s.pop(); }
      printf("%c", c);
    } else {
      s.push(c);
    }
  }
  while (!s.empty()) { printf("%c", s.top()); s.pop(); }
}
