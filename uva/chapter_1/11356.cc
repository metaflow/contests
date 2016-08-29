#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using vs = vector<string>; using msl = map<string, l>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

const vs months = {"January", "February", "March", "April", "May", "June",
"July", "August", "September", "October", "November", "December"};

tuple<l, l, l> to_ymd(string s) {
  // 1984-December-30
  //     a        b
  auto a = s.find('-');
  auto b = s.find('-', a + 1);
  l year = stol(s.substr(0, a).c_str());
  l month = 1;
  auto m = s.substr(a + 1, b - a - 1);
  while (m != months[month - 1]) month++;
  l day = stol(s.substr(b + 1).c_str());
  cerr << year << " " << m << " " << day << endl;
  return tie(year, month, day);
}

l days_in_year(l y) {
  if ((y % 4 == 0) and (y % 100 != 0 or y % 400 == 0)) return 366;
  return 365;
}

l days_in_month(l y, l m) {
  switch (m) {
    case 1: return 31;
    case 2: return 28 + days_in_year(y) - 365;
    case 3: return 31;
    case 4: return 30;
    case 5: return 31;
    case 6: return 30;
    case 7: return 31;
    case 8: return 31;
    case 9: return 30;
    case 10: return 31;
    case 11: return 30;
    case 12: return 31;
  }
  assert(false);
  return 0;
}

string from_ymd(l y, l m, l d) {
  stringstream ss;
  ss << y << "-" << months[m - 1] << "-" << setfill('0') << setw(2) << d;
  return ss.str();
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  for (l tc = 1; tc <= tcc; tc++) {
    l y, m, d;
    string s; cin >> s;
    tie(y, m, d) = to_ymd(s);
    l k; cin >> k;
    while (k) {
      l t = days_in_year(y);
      if (d == 1 and m == 1 and k >= t) {
        y++;
        k -= t;
        continue;
      }
      t = days_in_month(y, m);
      if (d == 1 and k >= t) {
        m++;
        k -= t;
        if (m == 13) {
          y++;
          m = 1;
        }
        continue;
      }
      l x = min(t - d + 1, k);
      d += x;
      k -= x;
      if (d == t + 1) {
        m++;
        d = 1;
        if (m == 13) {
          m = 1;
          y++;
        }
      }
    }
    cout << "Case " << tc << ": " << from_ymd(y, m, d) << endl;
  }
}
