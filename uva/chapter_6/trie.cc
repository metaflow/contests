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

void csort(vi &sa, vi &ra, int k, int n) {
  int i, j;
  vi c(max(n,255), 0);
  int m = 1;
  for (i = 0; i < n; ++i) {
    j = 0;
    if (i + k < n) j = ra[i + k];
    ++c[j];
    m = max(m, j + 1);
  }

  int s = 0;
  for (i = 0; i < m; ++i) {
    int t = s + c[i];
    c[i] = s;
    s = t;
  }

  vi tsa(n);

  for (i = 0; i < n; ++i) {
    j = 0;
    if (sa[i] + k < n) j = ra[sa[i] + k];
    tsa[c[j]++] = sa[i];
  }
  tsa.swap(sa);
}

vi construct_trie(string &s) {
  int i, j;
  int n = s.size();
  vi sa(n);
  for (i = 0; i < n; ++i) sa[i] = i;
  vi ra(n);
  for (i = 0; i < n; ++i) ra[i] = s[i];
  vi tra(n);
  for (i = 1; i < n; i <<= 1) {
    csort(sa, ra, i, n);
    csort(sa, ra, 0, n);
    tra[sa[0]] = 0;
    int r = 0;
    for (j = 1; j < n; ++j) {
      if ((ra[sa[j]] == ra[sa[j - 1]])
          && (ra[sa[j] + i] == ra[sa[j - 1] + i])) {
        tra[sa[j]] = r;
        continue;
      }
      tra[sa[j]] = ++r;
    }
    tra.swap(ra);
    if (ra[sa[n - 1]] == n - 1) break;
  }
  return sa;
}

int main() {
  string s;
  cin >> s;
  s += '$';
  vi trie = construct_trie(s);
  for (auto i : trie) {
    cout << s.substr(i) << endl;
  }
}
