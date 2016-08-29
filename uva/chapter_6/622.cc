#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

bool err;

int E(stringstream &s);

int F(stringstream &s) {
  int t = 0;
  if (s.peek() >= '0' && s.peek() <= '9') {
    s >> t;
  } else if (s.peek() == '(') {
    s.get();
    t = E(s);
    if (s.get() != ')') err = true;
  } else {
    err = true;
  }
  return t;
}

int C(stringstream &s) {
  int t = F(s);
  if (s.peek() == '*') {
    s.get();
    t *= C(s);
  }
  return t;
}

int E(stringstream &s) {
  int t = C(s);
  if (s.peek() == '+') {
    s.get();
    t = t + E(s);
  }
  return t;
}

int main() {
  int n;
  cin >> n;
  while (n--) {
    string s;
    cin >> s;
    stringstream ss(s);
    err = false;
    int r = E(ss);
    if (!ss.eof()) err = true;
    if (err) {
      cout << "ERROR" << endl;
    } else {
      cout << r << endl;
    }
  }
}
