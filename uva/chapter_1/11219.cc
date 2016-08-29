#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

struct Date {
  l y, m, d;
};

Date str_to_date(string s) {
  Date result;
  // DD/MM/YYYY
  // 0123456789
  result.d = stol(s.substr(0, 2).c_str());
  result.m = stol(s.substr(3, 2).c_str());
  result.y = stol(s.substr(6, 4).c_str());
  return result;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc;
  cin >> tcc;
  for (l tc = 1; tc <= tcc; tc++) {
    string a, b;
    cin >> a >> b;
    Date current = str_to_date(a), birth = str_to_date(b);
    l d = current.y - birth.y;
    if (current.m < birth.m || (current.m == birth.m && current.d < birth.d)) d--;
    cout << "Case #" << tc << ": ";
    if (d < 0) {
      cout << "Invalid birth date";
    } else if (d > 130) {
      cout << "Check birth date";
    } else {
      cout << d;
    }
    cout << endl;
  }
}
