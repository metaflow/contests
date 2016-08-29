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

struct token {
  char t; // +-*#
  string s;
};

map<string, token> tokens;

token get_token(string &s) {
  if (tokens.count(s)) {
    return tokens[s];
  }
  token r = {'#', s};
  return r;
}

void process(string &a, string &b, char op, string c) {
  auto ta = get_token(a);
  auto tb = get_token(b);

  token tc;
  tc.t = op;

  bool esc = false;
  switch (ta.t) {
    case '+':
    case '-':
      esc = (op == '*');
      break;
  }
  if (esc) {
    tc.s = "(" + ta.s + ")";
  } else {
    tc.s = ta.s;
  }

  tc.s += tc.t;
  esc = false;
  switch (tb.t) {
    case '+':
    case '-':
      esc = true;
      break;
    case '*':
      esc = (op == '*');
      break;
  }

  if (esc) {
    tc.s += "(" + tb.s + ")";
  } else {
    tc.s += tb.s;
  }

  tokens[c] = tc;
}

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; ++tc) {
    int n;
    cin >> n;
    tokens.clear();
    string c, eq, a, b;
    char op;
    while (n--) {
      cin >> c >> eq >> a >> op >> b;
      process(a, b, op, c);
    }
    printf("Expression #%d: %s\n", tc, tokens[c].s.c_str());
  }
}

// time : 25:21
