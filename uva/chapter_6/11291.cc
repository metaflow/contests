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

double read_expression(stringstream &s) {
  while (s && s.peek() == ' ') s.get();
  double r;
  if (s.peek() == '(') {
    s.get();
    double a, b, p;
    s >> p;
    a = read_expression(s);
    b = read_expression(s);
    while (s && s.get() != ')') {}
    r = p * (a + b) + (1 - p) * (a - b);
  } else {
    s >> r;
  }
  return r;
}

int main() {
  string s;
  while (getline(cin, s)) {
    if (s == "()") break;
    stringstream ss(s);
    double d = read_expression(ss);
    d = round(d * 100) / 100;
    printf("%.2f\n", d);
  }
}

// time : 22:05
