#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n;
  string s;
  while (cin >> n) {
    cin >> s;
    map<string, int> freq;
    int m = 0;
    string password;
    for (size_t i = 0; i < s.size() - n + 1; i++) {
      string w = s.substr(i, n);
      freq[w]++;
      if (freq[w] > m) {
        m = freq[w];
        password = w;
      }
    }
    cout << password << endl;
  }
}
