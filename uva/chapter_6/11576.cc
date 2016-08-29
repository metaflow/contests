#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int back[200];

void create_back(string &s) {
  int j = -1;
  back[0] = -1;
  for (int i = 0; i < s.size(); i++) {
    while (j >= 0 && s[j] != s[i]) j = back[j];
    j++;
    back[i + 1] = j;
  }
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int n, k;
    cin >> n >> k;
    string a, b;
    cin >> a;
    int total = n * k;
    for (int i = 0; i < k - 1; i++) {
      cin >> b;
      create_back(b);
      int j = 0;
      for (auto c : a) {
        while (j >= 0 && b[j] != c) j = back[j];
        j++;
      }
      total -= j;
      a = b;
    }
    cout << total << endl;
  }
}
