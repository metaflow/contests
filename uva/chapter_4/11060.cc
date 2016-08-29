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
#include <memory>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;

struct beverage {
  bool picked;
  string name;
  vector<shared_ptr<beverage>> parents;
};

using BP = shared_ptr<beverage>;

stack<BP> toplogical_sort(vector<BP> &b, int left) {
  stack<BP> empty;
  if (left == 0) {
    return empty;
  }
  for (auto it : b) {
    if (it->picked) continue;
    bool ok = true;
    for (auto p : it->parents) {
      if (!(p->picked)) {
        ok = false;
        break;
      }
    }
    if (!ok) continue;
    it->picked = true;
    auto result = toplogical_sort(b, left - 1);
    result.push(it);
    return result;
  }
  return empty;
}

int main() {
  int n, m;
  int tc = 0;
  while (cin >> n) {
    ++tc;
    map<string, BP> by_name;
    vector<BP> ordered;
    while (n--) {
      string s;
      cin >> s;
      auto b = make_shared<beverage>();
      ordered.push_back(b);
      by_name[s] = b;
      b->name = s;
      b->picked = false;
    }
    cin >> m;
    while (m--) {
      string a, b;
      cin >> a >> b;
      by_name[b]->parents.push_back(by_name[a]);
    }
    auto t = toplogical_sort(ordered, ordered.size());
    printf("Case #%d: Dilbert should drink beverages in this order:", tc);
    while (!t.empty()) {
      printf(" %s", t.top()->name.c_str());
      t.pop();
    }
    printf(".\n\n");
  }
}
