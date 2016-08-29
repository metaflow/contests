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

const int MAX = 100010;
int back[MAX];
string s;

void index() {
  back[0] = -1;
  int i = 0;
  int j = -1;
  size_t t = s.size() - 1;
  while (i <= t) {
    while(j >= 0 && s[t-i] != s[t-j]) j = back[j];
    ++i; ++j;
    back[i] = j;
  }
}

int match() {
  int i = 0, j = 0;
  size_t t = s.size() - 1;
  while (i <= t) {
    while (j >= 0 && s[i] != s[t-j]) j = back[j];
    ++i; ++j;
  }
  return s.size() - j;
}

int main() {
  while (cin >> s) {
    index();
    int add = match();
    printf("%s", s.c_str());
    for (int i = add - 1; i >= 0; --i) printf("%c", s[i]);
    printf("\n");
  }
}

// time : 1:07:44
