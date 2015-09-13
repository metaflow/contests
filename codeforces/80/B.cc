//time 14:00
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
  string s;
  while (cin >> s) {
    ll h = atoi(s.substr(0, 2).c_str()) % 12;
    ll m = atoi(s.substr(3, 2).c_str());
    double ha = h * 360 / 12 + (double)(m) / 2;
    cout << ha << " " << m * 360 / 60 << endl;
  }
}
