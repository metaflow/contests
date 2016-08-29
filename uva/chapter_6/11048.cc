#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n;
  cin >> n;
  unordered_map<string, int> dictonary;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    dictonary[s] = i;
  }
  int q;
  cin >> q;
  while (q--) {
    string s;
    cin >> s;
    if (dictonary.count(s)) {
      /*
      as is a misspelling of is
the is unknown
dictonary is a misspelling of dictionary
*/
      printf("%s is correct\n", s.c_str());
      continue;
    }
    int best = n;
    string correct;
    // add letter
    for (int i = 0; i <= s.size(); i++) {
      for (char c = 'a'; c <= 'z'; c++) {
        string a = s.substr(0, i) + c + s.substr(i);
        if (dictonary.count(a) == 0) continue;
        if (best < dictonary[a]) continue;
        best = dictonary[a];
        correct = a;
      }
    }
    // remove
    for (int i = 0; i < s.size(); i++) {
      string a = s.substr(0, i) + s.substr(i + 1);
      if (dictonary.count(a) == 0) continue;
      if (best < dictonary[a]) continue;
      best = dictonary[a];
      correct = a;
    }
    // swap letters
    for (int i = 0; i < s.size() - 1; i++) {
      string a = s;
      swap(a[i], a[i + 1]);
      if (dictonary.count(a) == 0) continue;
      if (best < dictonary[a]) continue;
      best = dictonary[a];
      correct = a;
    }
    // replace letter
    for (int i = 0; i < s.size(); i++) {
      string a = s;
      for (char c = 'a'; c <= 'z'; c++) {
        a[i] = c;
        if (dictonary.count(a) == 0) continue;
        if (best < dictonary[a]) continue;
        best = dictonary[a];
        correct = a;
      }
    }
    if (best < n) {
      printf("%s is a misspelling of %s\n", s.c_str(), correct.c_str());
    } else {
      printf("%s is unknown\n", s.c_str());
    }
  }
}
