#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  string s;
  while (cin >> s, s != "0") {
    ll r = 0;
    ll a = 0;
    for (auto ic = s.crbegin(); ic != s.crend(); ic++) {
      a = (a << 1) + 1;
      r += a * (*ic - '0');
    }
    cout << r << endl;
  }
}
