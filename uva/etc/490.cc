#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  vector<string> lines;
  string s;
  size_t max_length = 0;
  while (getline(cin, s)) {
    max_length = max(max_length, s.size());
    lines.emplace_back(s);
  }
  for (int i = 0; i < max_length; i++) {
    for (int j = lines.size() - 1; j >= 0; j--) {
      if (lines[j].size() > i) {
        printf("%c", lines[j][i]);
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}
