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

int main() {
  string s;
  vector<string> kb = {
    "`1234567890-=",
    "QWERTYUIOP[]\\",
    "ASDFGHJKL;'",
    "ZXCVBNM,./"
  };
  while (getline(cin, s)) {
    for (auto c : s) {
      bool ok = false;
      for (auto line : kb) {
        auto i = line.find(c);
        if (i == -1) continue;
        ok = true;
        cout << line[i - 1];
      }
      if (!ok) cout << c;
    }
    cout << endl;
  }
}
