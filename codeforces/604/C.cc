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

default_random_engine source(random_device{}());

l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b)(source);
}

bool random_bool() {
  return random_in_range(0, 1) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "01";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size() - 1)];
  }
  return s;
}

l count_substring(string& s) {
  char t = ' ';
  l answer = 0;
  for (auto c : s) {
    if (c != t) {
      t = c;
      answer++;
    }
  }
  return answer;
}

l solve(l n, string s) {
  l a = n;
  for (int i = 1; i < n; i++) if (s[i] == s[i - 1]) { a = i; break; }
  l b = n;
  for (int i = n - 2; i >= 0; i--) if (s[i] == s[i + 1]) { b = i; break; }
  if (b < a) b = n - 1;
  //   if (a < n - 1 && s[a] != s[a + 1]) {
  //     a = b;
  //   } else {
  //     b = a;
  //   }
  // }
  for (int i = a; i <= b && i < n; i++) s[i] = '0' + (1 - (s[i] - '0'));
  // cerr << s << endl;
  return count_substring(s);
}

l solve_brute(l n, string s) {
  l best = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      string a = s;
      for (int k = i; k <= j; k++) a[k] = '0' + (1 - (a[k] - '0'));
      best = max(best, count_substring(a));
    }
  }
  return best;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s;
  l n;
  while (cin >> n >> s) {
  // for (int i = 0; i < 1000; i++) {
  //   n = random_in_range(1, 10);
  //   s = random_string(n);
    l a = solve(n, s);
    // l b = solve_brute(n, s);
    // if (a == b) continue;
    cout << a << endl;
  //   cout << b << endl;
  //   cout << s << endl;
  //   return 0;
  // }

  }
}
