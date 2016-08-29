#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int b;
  ios_base::sync_with_stdio(false);
  while (cin >> b, b) {
    string sa, sr; // a % r
    cin >> sa >> sr;
    ll r = 0;
    for (auto c : sr) {
      r = r * b + (c - '0');
    }
    int q = 0;
    for (auto c : sa) {
      q = (q * b + (c - '0')) % r;
    }
    stack<int> s;
    while (true) {
      s.push(q % b);
      q /= b;
      if (q == 0) break;
    }
    while (!s.empty()) {
      cout << s.top();
      s.pop();
    }
    cout << endl;
  }
}
