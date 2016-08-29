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
  int tcc;
  cin >> tcc;
  while (tcc--) {
    string s;
    cin >> s;
    vector<char> r(s.size() - 2);
    for (int i = 0; i < 8; ++i) {
      cin >> s;
      for (int j = 0; j < r.size(); ++j) {
        if (s[j + 1] == '\\') r[j] += (1 << i);
      }
    }
    cin >> s; // last
    for (auto c : r) cout << c;
    cout << endl;
  }
}

// time : 7:25
