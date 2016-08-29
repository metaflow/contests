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

vl letters(const string& s) {
  vl result(26);
  for (auto c : s) result[c - 'a']++;
  return result;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  for (l tc = 0; tc < tcc; tc++) {
    if (tc) cout << endl;
    l n; cin >> n;
    vector<pair<string, vl>> words;
    for (l i = 0; i < n; i++) {
      string s; cin >> s;
      words.emplace_back(s, letters(s));
    }
    string t;
    while (cin >> t) {
      if (t == "END") break;
      cout << "Anagrams for: " << t << endl;
      auto m = letters(t);
      vector<string> matches;
      for (auto& w : words) {
        if (w.second == m) matches.emplace_back(w.first);
      }
      if (matches.empty()) {
        cout << "No anagrams for: " << t << endl;
      } else {
        for (l i = 1; i <= matches.size(); i++) {
          cout << setw(3) << setfill(' ') << i << ") " << matches[i - 1] << endl;
        }
      }
    }
  }
}
