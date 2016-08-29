#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  string dvorak = string("`123qjlmfp/[]")
  + "456.orsuyb;=\\"
  + "789aehtdck-"
  + "0zx,inwvg'"
  + "~!@#QJLMFP?{}" +
  + "$%^>ORSUYB:+|"
  + "&*(AEHTDCK_"
  + ")ZX<INWVG\"";
  string qwerty = string("`1234567890-=")
  + "qwertyuiop[]\\"
  + "asdfghjkl;'"
  + "zxcvbnm,./"
  + "~!@#$%^&*()_+"
  + "QWERTYUIOP{}|"
  + "ASDFGHJKL:\""
  + "ZXCVBNM<>?";
  string s;
  while (getline(cin,s)) {

    for (char c : s) {
      bool found = false;

      for (int i = 0; i < qwerty.size(); i++) {
        if (c != qwerty[i]) continue;
        printf("%c", dvorak[i]);
        found = true;
        break;
      }
      if (!found) printf("%c", c);
    }
    printf("\n");
  }
}
