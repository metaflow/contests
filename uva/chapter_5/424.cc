#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  vector<stack<int>> v;
  string s;
  while (cin >> s, s != "0") {
    v.emplace_back();
    for (auto c = s.cbegin(); c != s.cend(); c++) {
      v.back().push(*c - '0');
    }
  }
  stack<int> r;
  int c = 0;

  while (true) {
    c /= 10;
    bool f = true;
    for (auto &a : v) {
      if (a.empty()) continue;
      f = false;
      c += a.top(); a.pop();
    }
    if (c == 0 && f) break;
    r.push(c % 10);
  }
  while (!r.empty() && r.top() == 0) r.pop();
  while (!r.empty()) {
    printf("%d", r.top());
    r.pop();
  }
  printf("\n");
}
