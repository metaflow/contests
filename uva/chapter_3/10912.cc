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

const int MAX_S = 351;
const int MAX_L = 26;

int main() {
  int ways[MAX_S + 1][MAX_L + 1][MAX_L + 1];
  fill(&ways[0][0][0], &ways[MAX_S + 1][0][0], 0);
  for (int s = 1; s <= MAX_S; s++) {
    for (int l = 1; l <= MAX_L; l++) {
      for (int k = MAX_L; k >= 1; k--) {
        if (l == 1) {
          if (s >= k && s <= MAX_L) ways[s][l][k] = 1;
          continue;
        }
        if (k == MAX_L || s <= k) continue;
        ways[s][l][k] = ways[s - k][l - 1][k + 1] + ways[s][l][k + 1];
      }
    }
  }
  int tc = 0;
  int l, s;
  while (scanf("%d%d", &l, &s), l > 0) {
    printf("Case %d: ", ++tc);
    if (l > MAX_L || s > MAX_S) {
      printf("0\n");
    } else {
      printf("%d\n", ways[s][l][1]);
    }
  }
}
