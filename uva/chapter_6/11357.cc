#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

using si = string::iterator;
const int MAX = 26;
bool sat = false;
int state[MAX];

void literal(si &p) {
  int v = 1;
  if (*p == '~') {
    v = 2;
    p++;
  }
  int t = *p - 'a';
  state[t] = state[t] | v;
  p++;
}

void cause(si &p) {
  fill(&state[0], &state[MAX], 0);
  p++; // '('
  while (true) {
    literal(p);
    if (*p == '&') {
      p++;
      continue;
    }
    p++; // ')'
    break;
  }
  int m = 0;
  for (int i = 0; i < MAX; i++) m = max(m, state[i]);
  sat = sat || (m < 3);
}

void formula(si &p, si end) {
  while (true) {
    cause(p);
    if (p == end) break;
    p++;
  }
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    string s;
    cin >> s;
    sat = false;
    si b = s.begin();
    formula(b, s.end());
    if (sat) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
