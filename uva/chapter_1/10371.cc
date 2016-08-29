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

map<string, l> shift = {
{"UTC", 0*60},
{"GMT", 0*60},
{"BST", +1*60},
{"IST", +1*60},
{"WET", 0*60},
{"WEST", 1*60},
{"CET", 1*60},
{"CEST", 2*60},
{"EET", 2*60},
{"EEST", 3*60},
{"MSK", 3*60},
{"MSD", 4*60},
{"AST", -4*60},
{"ADT", -3*60},
{"NST", -3*60 - 30},
{"NDT", -2*60 - 30},
{"EST", -5*60},
{"EDT", -4*60},
{"CST", -6*60},
{"CDT", -5*60},
{"MST", -7*60},
{"MDT", -6*60},
{"PST", -8*60},
{"PDT", -7*60},
{"HST", -10*60},
{"AKST", -9*60},
{"AKDT", -8*60},
{"AEST", 10*60},
{"AEDT", 11*60},
{"ACST", 9*60 + 30},
{"ACDT", 10*60 + 30},
{"AWST", 8*60},
};

l read_time(stringstream& ss) {
  string s; ss >> s;
  auto p = s.find(':');
  if (p == string::npos) {
    if (s == "noon") return 12 * 60;
    return 0;
  }
  l h = atol(s.substr(0, p).c_str()) % 12;
  l m = atol(s.substr(p + 1).c_str());
  // cerr << h << " " << m << endl;
  string ampm; ss >> ampm;
  if (ampm == "p.m.") h += 12;
  return h * 60 + m;
}

string format_time(l time) {
  time = (time + 24 * 60) % (24 * 60);
  if (time == 0) return "midnight";
  if (time == 12 * 60) return "noon";
  l h = time / 60;
  bool pm = h >= 12;
  h = (h + 11) % 12 + 1;
  l m = time % 60;
  char buffer[100];
  sprintf(buffer, "%lld:%02lld %s", h, m, pm ? "p.m." : "a.m.");
  return string(buffer);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n; cin >> n;
  string s;
  getline(cin, s);
  while (n--) {
    getline(cin, s);
    stringstream ss(s);
    l t = read_time(ss);
    string from, to; ss >> from >> to;
    cout << format_time(t - shift[from] + shift[to]) << endl;
  }
}
