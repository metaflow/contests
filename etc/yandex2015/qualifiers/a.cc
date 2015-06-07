#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  string w;
  getline(cin, w);
  int n; cin >> n;
  set<string> dict;
  while (n--) {
    string s;
    cin >> s;
    dict.insert(s);
  }
  stringstream ss(w);
  string s;
  while (ss >> s) {
    if (dict.count(s) == 0) {
      printf("Misspell\n");
      return 0;
    }
  }
  printf("Correct\n");
}
