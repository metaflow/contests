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
  string s;
  getline(cin, s);
  while (tcc--) {
    getline(cin, s);
    getline(cin, s);
    stringstream ss(s);

    vi p;
    int i;
    while (ss >> i) p.emplace_back(i - 1);
    vector<string> d(p.size());
    getline(cin, s);
    ss.str(s);
    ss.clear();

    for (auto i : p) ss >> d[i];
    for (auto a : d) cout << a << endl;

    if (tcc) cout << endl;
  }
}
