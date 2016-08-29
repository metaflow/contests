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
  string a, b;
  while (getline(cin, a)) {
    vi ca(26), cb(26);
    getline(cin, b);
    for (auto c : a) ca[c - 'a']++;
    for (auto c : b) cb[c - 'a']++;
    for (int i = 0; i < ca.size(); ++i) {
      for (int j = 0; j < min(ca[i], cb[i]); ++j) {
        cout << (char)('a' + i);
      }
    }
    cout << endl;
  }
}

// time: 19:15
