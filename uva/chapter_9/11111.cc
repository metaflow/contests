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
    stringstream ss(s);
    stack<ii> toys;
    bool ok = true;
    int a;
    while (ss >> a) {
      if (a < 0) {
        toys.emplace(a, -a);
        continue;
      }
      if (toys.empty()) {
        ok = false;
        break;
      }
      auto t = toys.top();
      toys.pop();
      if (t.first != -a) {
        ok = false;
        break;
      }
      if (!toys.empty()) {
        toys.top().second -= a;
        if (toys.top().second <= 0) {
          ok = false;
          break;
        }
      }
    }
    ok = ok && toys.empty();
    if (ok) {
      cout << ":-) Matrioshka!" << endl;
    } else {
      cout << ":-( Try again." << endl;
    }
  }
}
