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

vector<string> haab_months = {
  "pop",
  "no",
  "zip",
  "zotz",
  "tzec",
  "xul",
  "yoxkin",
  "mol",
  "chen",
  "yax",
  "zac",
  "ceh",
  "mac",
  "kankin",
  "muan",
  "pax",
  "koyab",
  "cumhu",
};

vector<string> tzolkin_days = {
  "imix",
  "ik",
  "akbal",
  "kan",
  "chicchan",
  "cimi",
  "manik",
  "lamat",
  "muluk",
  "ok",
  "chuen",
  "eb",
  "ben",
  "ix",
  "mem",
  "cib",
  "caban",
  "eznab",
  "canac",
  "ahau"
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  cout << tcc << endl;
  for (l tc = 0; tc < tcc; tc++) {
    l day; cin >> day; string month; cin >> month >> month;
    l year; cin >> year;
    l date = year * 365;
    auto m = find(haab_months.begin(), haab_months.end(), month);
    date += distance(haab_months.begin(), m) * 20;
    date += day;
    // cout << date << endl;
    year = date / 260;
    date %= 260;
    cout << (1 + date % 13) << " " << tzolkin_days[date % 20] << " " << year << endl;
    // cout << day << " " << month << " " << year << endl;
  }
}
