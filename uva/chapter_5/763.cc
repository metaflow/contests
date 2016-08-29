#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

void convert(string &s, vi &a) {
  int i = 0;
  for (auto c = s.crbegin(); c != s.crend(); c++) {
    a[i++] = (*c) - '0';
  }
}

int main() {
  string s;
  bool nl = false;
  while (cin >> s) {
    if (nl) cout << endl;
    nl = true;
    vi a(110, 0), b(110, 0);
    convert(s, a);
    cin >> s;
    convert(s, b);
    for (int i = 0; i < a.size(); i++) a[i] += b[i];
    int i = 0;
    while (i < a.size()) {
      if (a[i] > 1) {
        a[i] -= 2;
        a[i + 1]++;
        if (i > 1) {
          a[i - 2]++;
          i -= 2;
        } else if (i == 1) {
          a[i - 1]++;
          i--;
        }
        continue;
      }
      i++;
    }
    i = a.size() - 1;
    while (i > 0) {
      if (a[i] == 1 && a[i - 1] == 1) {
        a[i + 1]++;
        a[i] = 0;
        a[i - 1] = 0;
        i += 2;
        continue;
      }
      i--;
    }
    i = a.size() - 1;
    while (i > 0 && a[i] == 0) i--;
    while (i >= 0) cout << a[i--];
    cout << endl;
  }
}

// time 44m
