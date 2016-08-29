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
  ll i, count, j;
  j = 1500;
  priority_queue<ll, vector<ll>, std::greater<ll>> pq;
  pq.push(1);
  ll last = 0;
  count = 0;
  while (true) {
    i = pq.top(); pq.pop();
    if (last == i) continue;
    count++;
    last = i;
    pq.push(i * 2);
    pq.push(i * 3);
    pq.push(i * 5);
    if (count == j) {
      printf("The %lld'th ugly number is %lld.\n", j, i);
      return 0;
    }
  }
}
