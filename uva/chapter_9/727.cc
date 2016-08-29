#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  string s; getline(cin, s); getline(cin, s);
  for (int tc = 1; tc <= tcc; tc++) {
    if (tc != 1) cout << endl;
    stack<char> p;
    while (getline(cin, s), s.size()) {
      char c = s[0];
      if (c >= '0' && c <= '9') { cout << c; continue; }
      switch (c) {
        case '(': p.push('('); break;
        case ')': {
          while (true) {
              auto a = p.top(); p.pop();
              if (a == '(') break;
              cout << a;
            }
          };
          break;
        case '+':
        case '-':
          while (!p.empty() && p.top() != '(') {
            cout << p.top(); p.pop();
          }
          p.push(c);
          break;
        case '*':
        case '/':
          while (!p.empty()) {
            auto a = p.top();
            if (a == '(' || a == '+' || a == '-') break;
            cout << a;
            p.pop();
          }
          p.push(c);
          break;
      }
    }
    while (!p.empty()) {
      cout << p.top(); p.pop();
    }
    cout << endl;
  }
}
