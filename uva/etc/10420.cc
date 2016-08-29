#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  size_t n;
  cin >> n;
  map<string, size_t> count;
  string s;
  getline(cin, s);
  while (n--) {
    getline(cin, s);
    istringstream ss(s);
    string country; ss >> country;
    if (!count.count(country)) {
      count[country] = 0;
    }
    count[country]++;
  }
  for (auto k : count) {
    cout << k.first << " " << k.second << endl;
  }
}

