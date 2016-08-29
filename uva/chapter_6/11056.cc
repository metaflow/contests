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
using record = pair<llu, string>;

int main() {
  int n;
  while (cin >> n) {
    vector<record> pilots;
    while (n--) {
      string name, e;
      llu m, s, ms;
      cin >> name >> e >> m >> e >> s >> e >> ms >> e;
      s += m * 60;
      ms += s * 1000;
      pilots.emplace_back(ms, name);
    }
    int row = 0;
    sort(pilots.begin(), pilots.end(), [](const record &a, const record &b) {
      if (a.first != b.first) return a.first < b.first;
      return lexicographical_compare(a.second.begin(), a.second.end(), b.second.begin(), b.second.end(), [](string::value_type a, string::value_type b) {
          return tolower(a) < tolower(b);
      });
    });
    for (size_t i = 0; i < pilots.size(); ++i) {
      if (i % 2 == 0) {
        ++row;
        printf("Row %d\n", row);
      }
      printf("%s\n", pilots[i].second.c_str());
    }
    printf("\n");
  }
}

// time : 20:00
