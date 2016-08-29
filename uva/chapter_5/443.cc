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

const int MAX = 5842;

ll m[MAX];

void precompute() {
  priority_queue<ll, vector<ll>, greater<ll>> q;
  q.push(1);
  int i = 0;
  ll p = 0;
  while (i < MAX) {
    ll a = q.top(); q.pop();
    if (a == p) continue;
    p = a;
    m[i] = a;
    ++i;
    q.push(a * 2);
    q.push(a * 3);
    q.push(a * 5);
    q.push(a * 7);
  }
}

string ordinal_suffix(int n) {
  if (n % 100 / 10 == 1) {
    return "th";
  }
  int i = n % 10;
  if (i == 1) return "st";
  if (i == 2) return "nd";
  if (i == 3) return "rd";
  return "th";
}

int main() {
  precompute();
  int n;
  while (cin >> n, n) {
    printf("The %d%s humble number is %lld.\n",
      n, ordinal_suffix(n).c_str(), m[n - 1]);
  }
}
