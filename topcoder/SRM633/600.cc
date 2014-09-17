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
using bits = bitset<50>;
struct node;

using pnode = shared_ptr<node>;
using graph = vector<pnode>;

struct node {
  int v;
  graph adjusted;
};

class DoubleTree {
public:
  graph A, B;
  bits getpath(pnode u, pnode v) {
    stack<pnode> s;
    s.push(u);
    bits visited;
    bits result;
    while (!s.empty()) {
      auto x = s.top();
      visited[x->v] = true;
      if (x == v) {
        while (!s.empty()) {
          result[s.top()->v] = true;
          s.pop();
        }
        break;
      }
      bool ok = false;
      for (auto y : x->adjusted) {
        if (visited[y->v]) continue;
        s.push(y);
        ok = true;
        break;
      }
      if (ok) continue;
      s.pop();
    }
    return result;
  }

  vi sc;

  int check(bits e, pnode ra, pnode rb, int n, int current) {
    stack<int> s;
    s.push(n);
    while (!s.empty()) {
      int k = s.top();
      s.pop();
      if (e[k]) continue;
      auto p = getpath(ra, A[k]);
      for (int i = 0; i < 50; ++i) {
        if (!p[i]) continue;
        if (e[i]) continue;
        s.push(i);
        current += sc[i];
      }
      p = getpath(rb, B[k]);
      for (int i = 0; i < 50; ++i) {
        if (!p[i]) continue;
        if (e[i]) continue;
        s.push(i);
        current += sc[i];
      }
    }

    if (current <= 0) return 0;
    int best = current;
    for (auto x : A[n]->adjusted) {
      if (e[x->v]) continue;
      best = max(best, check(e, ra, rb, x->v, current));
    }
    return best;
  }

  int maximalScore(vector <int> a, vector <int> b,
    vector <int> c, vector <int> d, vector <int> score) {
    sc = score;
    int n = a.size() + 1;
    A.resize(n);
    B.resize(n);
    for (int i = 0; i < n; ++i) {
      A[i] = make_shared<node>();
      A[i]->v = i;
      B[i] = make_shared<node>();
      B[i]->v = i;
    }

    for (int i = 0; i < a.size(); ++i) {
      A[a[i]]->adjusted.push_back(A[b[i]]);
      A[b[i]]->adjusted.push_back(A[a[i]]);
      B[c[i]]->adjusted.push_back(B[d[i]]);
      B[d[i]]->adjusted.push_back(B[c[i]]);
    }

    int best = 0;

    for (int i = 0; i < n; ++i) {
      bits e;
      best = max(best, check(e, A[i], B[i], i, 0));
    }

    return best;
  }
};

int main() {
  DoubleTree dt;
  dt.maximalScore({0,0,1}, {1,3,2}, {0,0,3}, {1,3,2}, {1000,24,100,-200});
}
