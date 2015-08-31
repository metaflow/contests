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

bool consolant(char c) {
  switch (c) {
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
    case 'Y':
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
    case 'y':
    return false;
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s;
  char q = 0;
  while (getline(cin, s)) {
    for (ll i = 0; i < (ll)s.size(); i++) {
      char c = s[i];
      if (isalpha(c)) {
        string w = "";
        w += c;
        while (i + 1 < s.size() && isalpha(s[i + 1])) {
           i++;
           w += s[i];
        }
        if (w == "done") {
          cout << endl;
          return 0;
        }
        if (q) cout << q;
        q = 0;
        bool uc = isupper(w[0]);
        ll p = 0;
        while (p < w.size() && consolant(w[p])) p++;
        if (p == 0) {
          w += "way";
        } else {
          w = w.substr(p) + w.substr(0, p) + "ay";
        }
        for (auto &c : w) c = tolower(c);
        if (uc) w[0] = toupper(w[0]);
        cout << w;
      } else {
        if (q) cout << q;
        q = c;
      }
    }
    if (q) cout << q;
    q = 0;
    cout << endl;
  }
}
