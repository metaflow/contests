#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

char table[5][5];
ii pos[26];

void create_table(string s) {
  bitset<26> used; used.reset();
  used['q' - 'a'] = true;
  int p = 0;

  s += "abcdefghijklmnopqrstuvwxyz";

  for (char c : s) {
    if (c >= 'a' && c <= 'z') {
      if (used[c - 'a']) continue;
      used[c - 'a'] = true;
      pos[c - 'a'] = make_pair(p / 5, p % 5);
      table[p / 5][p % 5] = toupper(c);
      p++;
    }
  }

  // for (int i = 0; i < 5; i++) {
  //   for (int j= 0; j < 5; j++) printf("%c", table[i][j]);
  //   printf("\n");
  // }
}

string encrypt_pair(char a, char b) {
  auto pa = pos[a - 'a'];
  auto pb = pos[b - 'a'];
  if (pa.first == pb.first) {
    pa.second++;
    pb.second++;
  } else if (pa.second == pb.second) {
    pa.first++;
    pb.first++;
  } else {
    swap(pa.second, pb.second);
  }
  string e = "  ";
  e[0] = table[pa.first % 5][pa.second % 5];
  e[1] = table[pb.first % 5][pb.second % 5];
  // printf("%c%c -> %s\n", a, b, e.c_str());
  return e;
}

string encrypt(string s) {
  string e;
  for (size_t i = 0; i < s.size(); i++) {
    if (i + 1 == s.size() || s[i] == s[i + 1]) {
      e += encrypt_pair(s[i], 'x');
    } else {
      e += encrypt_pair(s[i], s[i + 1]);
      i++;
    }
  }
  return e;
}

string normalize(string s) {
  string r = "";
  for (char c : s) {
    if (c >= 'a' && c <= 'z') r += c;
  }
  return r;
}

int main() {
  int tcc;
  string s;
  cin >> tcc;
  getline(cin, s);
  while (tcc--) {
    getline(cin, s);
    create_table(normalize(s));
    getline(cin, s);
    cout << encrypt(normalize(s)) << endl;
  }
}
