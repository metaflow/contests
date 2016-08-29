#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  string a, b;
  while (cin >> a >> b) {
    auto ib = b.cbegin();
    auto ia = a.cbegin();
    while (ia != a.cend()) {
      while (ib != b.cend() && *ia != *ib) ib++;
      if (ib == b.cend()) break;
      ib++;
      ia++;
    }
    if (ia == a.cend()) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
}
