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

int best;

int gcd(int a, int b) {
  if (b == 0) return a;
  if (b < best) return 1;
  return gcd(b, a % b);
}

int main() {
  int tcc;
  cin >> tcc;
  string s;
  getline(cin, s); // skip \n
  while (tcc--) {
    getline(cin, s);
    stringstream ss(s);
    vi v;
    int i;
    while (ss >> i) v.push_back(i);
    best = 0;
    for (int i = 0; i < v.size(); ++i) {
      for (int j = i + 1; j < v.size(); ++j) {
        best = max(best, gcd(v[i], v[j]));
      }
    }
    cout << best << endl;
  }
}
