#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 100001;

int position[MAX];
int length[MAX];
int reach[MAX];
int ft[2 * MAX];

int main() {
  int n;
  while (cin >> n) {
    for (int i = 0; i < n; i++) cin >> position[i] >> length[i];
    int q;
    for (int i = 0; i < n; i++) {
      reach[i] = position[i] + length[i];
    }

    cin >> q;
    while (q--) {
      int f, t;
      cin >> f >> t; f--; t--;
    }
  }
}
