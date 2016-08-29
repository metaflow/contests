#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <queue>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

bool match(string &a, string &b) {
  return (a[0] == b[0]) || (a[1] == b[1]);
}

int main() {
  int i;
  while (true) {
    string s;
    cin >> s;
    if (s == "#") break;
    list<stack<string>> row(52);
    auto q = row.begin();
    q->push(s);
    for (i = 0; i < 51; i++) {
      q++;
      cin >> s;
      q->push(s);
    }

    q = row.begin(); q++;
    while (q != row.end()) {
      auto w = q;
      for (i = 0; i < 3 && w != row.begin(); i++) w--;
      bool f = (i == 3 && match(w->top(), q->top()));
      if (!f) {
        w = prev(q);
        f = match(w->top(), q->top());
      }
      if (f) {
        w->push(q->top()); q->pop();
        if (q->empty()) row.erase(q);
        q = w;
        if (q == row.begin()) q++;
      } else {
        q++;
      }
    }

    if (row.size() == 1) {
      printf("1 pile remaining:");
    } else {
      printf("%lu piles remaining:", row.size());
    }
    for (auto a : row) printf(" %lu", a.size());
    printf("\n");
  }
}
