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

int popcount(int n) {
  n = n - ((n >> 1) & 0x55555555);
  n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
  n = (n & 0x0F0F0F0F) + ((n >> 4) & 0x0F0F0F0F);
  n = (n & 0x00FF00FF) + ((n >> 8) & 0x00FF00FF);
  n = (n & 0x0000FFFF) + ((n >> 16) & 0x0000FFFF);
  return n;
}

int main() {
  int n;
  while (cin >> n, n) {
    cout << "The parity of ";
    stack<int> s;
    int i = n;
    while (i) {
      s.push(i % 2);
      i >>= 1;
    }
    while (!s.empty()) {
      cout << s.top();
      s.pop();
    }
    cout << " is " <<  popcount(n) << " (mod 2)." << endl;
  }
}
