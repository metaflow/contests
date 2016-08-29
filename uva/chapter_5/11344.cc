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

vector<vector<ii>> cycles(13);

void create_cycles() {
  for (int i = 1; i < 13; ++i) {
    int m = 1 % i;
    vector<ii> &c = cycles[i];
    bool complete = false;
    while (true) {
      for (int j = 0; j < c.size(); ++j) {
        if (c[j].first == m) {
          c[c.size() - 1].second = j;
          complete = true;
        }
      }
      if (complete) break;
      if (!c.empty()) c[c.size() - 1].second = c.size();
      c.push_back(ii(m, 0));
      m = (m * 10) % i;
    }
  }
}

bool divisible(string s, vi d) {
  vi sums(13, 0);
  vi pos(13, 0);
  for (auto c = s.crbegin(); c != s.crend(); c++) {
    for (auto i : d) {
      int v = *c - '0';
      sums[i] += v * cycles[i][pos[i]].first;
      pos[i] = cycles[i][pos[i]].second;
    }
  }

  for (auto i : d) {
    if (sums[i] % i != 0) return false;
  }

  return true;
}

int main() {
  create_cycles();
  int tcc;
  cin >> tcc;
  while (tcc--) {
    string s;
    getline(cin, s); // skip empty
    getline(cin, s);
    int k;
    cin >> k;
    vi d;
    for (int i = 0; i < k; ++i) {
      int v;
      cin >> v;
      d.push_back(v);
    }
    if (divisible(s, d)) {
      cout << s << " - Wonderful." << endl;
    } else {
      cout << s << " - Simple." << endl;
    }
  }
}
