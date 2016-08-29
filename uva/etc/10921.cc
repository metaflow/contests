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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s;
  while (cin >> s) {
    for (auto &c : s) {
      switch (c) {
        case 'A': case 'B': case 'C': c = '2'; break;
        case 'D': case 'E': case 'F': c = '3'; break;
        case 'G': case 'H': case 'I': c = '4'; break;
        case 'J': case 'K': case 'L': c = '5'; break;
        case 'M': case 'N': case 'O': c = '6'; break;
        case 'P': case 'Q': case 'R': case 'S': c ='7'; break;
        case 'T': case 'U': case 'V': c = '8'; break;
        case 'W': case 'X': case 'Y': case 'Z': c ='9'; break;
      }
    }
    cout << s << endl;
  }
}
