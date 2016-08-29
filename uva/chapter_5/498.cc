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
  while (getline(cin, s)) {
    stringstream ss(s);
    vi c;
    int v;
    while (ss >> v) c.push_back(v);
    getline(cin, s);
    ss.str(s);
    ss.clear();
    bool first = true;
    while (ss >> v) {
      if (!first) cout << " ";
      first = false;
      ll p = 0;
      for (auto i : c) p = p * v + i;
      cout << p;
    }
    cout << endl;
  }
}
