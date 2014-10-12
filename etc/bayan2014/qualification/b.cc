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
  int tcc, i;
  cin >> tcc;
  while (tcc--) {
    string s;
    cin >> s;
    i = 0;
    for (auto c : s) {
      switch (c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u': i++;
      }
    }
    if (i % 2 == 1) {
      cout << "PESAR" << endl;
    } else {
      cout << "DOKHTAR" << endl;
    }
  }
}
