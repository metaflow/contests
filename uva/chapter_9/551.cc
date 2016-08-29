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
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s;
  while (getline(cin, s)) {
    int p = 0, i = 0;
    stack<int> quotes;
    int bad = 0;
    while (i < s.size()) {
      int q = 0;
      switch (s[i]) {
        case '{': q = 1; break;
        case '}': q = -1; break;
        case '[': q = 2; break;
        case ']': q = -2; break;
        case '<': q = 3; break;
        case '>': q = -3; break;
        case '(':
          q = 4;
          if (i + 1 < s.size() && s[i + 1] == '*') { q = 5; i++; }
          break;
        case ')': q = -4; break;
        case '*': if (i + 1 < s.size() && s[i + 1] == ')') { q = -5; i++; } break;
      }
      p++;
      i++;
      if (q == 0) continue;
      if (q > 0) { quotes.emplace(q); continue; }
      if (quotes.empty() || quotes.top() != -q) {
        bad = p;
        break;
      }
      quotes.pop();
    }
    if (!quotes.empty() && bad == 0) bad = p + 1;
    if (bad == 0) {
      cout << "YES" << endl;
    } else {
      cout << "NO " << bad << endl;
    }
  }
}
