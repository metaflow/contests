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
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;

const int MAX = 'Z' - 'A' + 1;

bool edge[MAX][MAX];

bool cycle;
bool available[MAX];

void backtrack(string solution, int left) {
  if (left == 0) {
    cout << solution << endl;
    cycle = false;
    return;
  }

  for (int i = 0; i < MAX; ++i) {
    if (!available[i]) continue;
    bool ok = true;
    for (int j = 0; j < MAX; ++j) {
      if (available[j] && edge[j][i]) {
        ok = false;
        break;
      }
    }
    if (!ok) continue;
    available[i] = false;

    if (solution.empty()) {
      backtrack({(char)('A' + i)}, left - 1);
    } else {
      backtrack(solution + " " + (char)('A' + i), left - 1);
    }

    available[i] = true;
  }
}

int main() {
    int tcc;
    cin >> tcc;
    while (tcc--) {
      fill(&edge[0][0], &edge[MAX][0], false);
      fill(&available[0], &available[MAX], false);
      cycle = true;

      string s;
      while (s.empty()) getline(cin, s);
      int count = 0;
      for (char c : s) {
        if (c >= 'A' && c <= 'Z') {
          available[c - 'A'] = true;
          ++count;
        }
      }
      s.erase();
      while (s.empty()) getline(cin, s);
      char from = ' ';
      for (char c : s) {
        if (c >= 'A' && c <= 'Z') {
          if (from == ' ') {
            from = c;
            continue;
          }
          edge[from - 'A'][c - 'A'] = true;
          from = ' ';
        }
      }

      backtrack("", count);
      if (cycle) cout << "NO" << endl;
      if (tcc) cout << endl;
    }
}
