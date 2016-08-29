#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  string s;
  int correct = 0;
  while (getline(cin, s)) {
    int a, b, c;
    char op, t;
    stringstream ss(s);
    ss >> a >> op >> b >> t;
    if (ss.peek() == '?') continue;
    ss >> c;
    switch (op) {
      case '+': if (a + b == c) correct++; break;
      case '-': if (a - b == c) correct++; break;
    }
  }
  cout << correct << endl;
}
