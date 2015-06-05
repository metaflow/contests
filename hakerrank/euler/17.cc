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

vector<pair<ll, string>> multipliers = {
{1000000000000, "Trillion"},
{1000000000, "Billion"},
{1000000, "Million"},
{1000, "Thousand"},
{100, "Hundred"}};

vector<pair<ll, string>> tens = {{90, "Ninety"},
{80, "Eighty"},
{70, "Seventy"},
{60, "Sixty"},
{50, "Fifty"},
{40, "Forty"},
{30, "Thirty"},
{20, "Twenty"}};

vector<string> under20 = {"Zero", "One", "Two", "Three", "Four", "Five", "Six",
"Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

vector<string> spell(ll n) {
  cerr << n << endl;
  for (auto m : multipliers) {
    if (n > m.first) {
      auto v = spell(n / m.first);
      cerr << m.second << endl;
      v.emplace_back(m.second);
      auto a = spell(n % m.first);
      v.insert(v.end(), a.begin(), a.end());
      return v;
    }
  }
  for (auto m : tens) {
    if (n > m.first) {
      vector<string> v;
      cerr << m.second << endl;
      v.emplace_back(m.second);
      auto a = spell(n % m.first);
      v.insert(v.end(), a.begin(), a.end());
      return v;
    }
  }
  vector<string> v;
  v.emplace_back(under20[n]);
  return v;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // for (int i = 0; i < 20; i++) {
  //   cout << i << " " << spell(i)[0] << endl;
  // }
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n; cin >> n;
    auto v = spell(n);
    bool first = true;
    for (auto s : v) {
      if (!first) cout << " ";
      first = false;
      cout << s;
    }
    cout << endl;
  }
}
