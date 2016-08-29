#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
enum Token { S, IF, ELSE, FI, END };
using Tokens = vector<Token>;
using TI = Tokens::iterator;

ll expressions(TI &p, TI end);
ll expression(TI &p, TI end);

ll program(TI &p, TI end) {
  ll r = expressions(p, end);
  p++; // END
  return r;
}

ll expressions(TI &p, TI end) {
  ll r = 1;
  ll t;
  while ((t = expression(p, end)) > 0) r *= t;
  return r;
}

ll expression(TI &p, TI end) {
  if (p == end) return 0;
  if (*p == S) { p++; return 1; }
  if (*p == IF) {
    p++; // IF
    ll r = expressions(p, end);
    p++; // ELSE;
    r += expressions(p, end);
    p++; // FI
    return r;
  }
  return 0;
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    string s;
    Tokens tokens;
    while (cin >> s) {
      Token t = END;
      if (s == "S") { t = S; }
      else if (s == "IF") { t = IF; }
      else if (s == "ELSE") { t = ELSE; }
      else if (s == "END_IF") { t = FI; }
      tokens.emplace_back(t);
      if (t == END) break;
    }
    auto p = tokens.begin();
    cout << program(p, tokens.end()) << endl;
  }
}
