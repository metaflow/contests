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
const l SIZE = 60;
using vs = vector<string>;

map<char, string> font5 = {
{'A',
" ***  "
"*   * "
"***** "
"*   * "
"*   * "},
{'B',
"****  "
"*   * "
"****  "
"*   * "
"****  "},
{'C',
" **** "
"*   * "
"*     "
"*     "
" **** "},
{'J',
"  *** "
"   *  "
"   *  "
"*  *  "
" **   "},
{'S',
" **** "
"*     "
" ***  "
"    * "
"****  "},
{'D',
"****  "
"*   * "
"*   * "
"*   * "
"****  "},
{'K',
"*   * "
"*  *  "
"***   "
"*  *  "
"*   * "},
{'T',
"***** "
"* * * "
"  *   "
"  *   "
" ***  "},
{'E',
"***** "
"*     "
"***   "
"*     "
"***** "},
{'L',
"*     "
"*     "
"*     "
"*     "
"***** "},
{'U',
"*   * "
"*   * "
"*   * "
"*   * "
" ***  "},
{'F',
"***** "
"*     "
"***   "
"*     "
"*     "},
{'M',
"*   * "
"** ** "
"* * * "
"*   * "
"*   * "},
{'V',
"*   * "
"*   * "
" * *  "
" * *  "
"  *   "},
{'G',
" **** "
"*     "
"*  ** "
"*   * "
" ***  "},
{'N',
"*   * "
"**  * "
"* * * "
"*  ** "
"*   * "},
{'W',
"*   * "
"*   * "
"* * * "
"** ** "
"*   * "},
{'H',
"*   * "
"*   * "
"***** "
"*   * "
"*   * "},
{'O',
" ***  "
"*   * "
"*   * "
"*   * "
" ***  "},
{'X',
"*   * "
" * *  "
"  *   "
" * *  "
"*   * "},
{'I',
"***** "
"  *   "
"  *   "
"  *   "
"***** "},
{'P',
"****  "
"*   * "
"****  "
"*     "
"*     "},
{'Y',
"*   * "
" * *  "
"  *   "
"  *   "
"  *   "},
{'Q',
" ***  "
"*   * "
"*   * "
"*  ** "
" **** "},
{'R',
"****  "
"*   * "
"****  "
"*  *  "
"*   * "},
{'Z',
"***** "
"   *  "
"  *   "
" *    "
"***** "},
{' ',
"      "
"      "
"      "
"      "
"      "},};

struct Command {
  enum Type { EOP, PRINT_C1, PRINT_C5 };
  Type type;
  l row, column;
  string content;
};

Command to_command(string s) {
  Command result;
  if (s == ".EOP") {
    result.type = Command::EOP;
    return result;
  }
  stringstream ss(s);
  string align;
  string font;
  ss >> align >> font;
  l width = (font == "C1" ? 1 : 6);
  // cout << "font " << font << endl;
  result.type = (font == "C1" ? Command::PRINT_C1 : Command::PRINT_C5);
  ss >> result.row;
  result.row--;
  if (align == ".P") {
    ss >> result.column;
    result.column--;
  }
  getline(ss, result.content);
  auto pos = result.content.find('|') + 1;
  result.content = result.content.substr(pos, result.content.size() - pos - 1);
  width *= result.content.size();
  if (align == ".L") {
    result.column = 0;
  }
  if (align == ".C") {
    result.column = (SIZE / 2) - width / 2;
  }
  if (align == ".R") {
    result.column = SIZE - width;
  }
  return result;
}

void put_character(char c, l row, l column, vs& buffer) {
  if (row < 0 || row >= SIZE || column < 0 || column >= SIZE || c == ' ')
    return;
  buffer[row][column] = c;
}

void output_c1(l row, l column, string& s, vs& buffer) {
  // cout << s << " # 1 @ " << row << " " << column << endl;
  for (l i = 0; i < (l)s.size(); i++) {
    put_character(s[i], row, column + i, buffer);
  }
}

void put_character_5(char c, l row, l column, vs& buffer) {
  if (!font5.count(c)) {
    cout << c << " not found in font5" << endl;
    return;
  }
  for (l i = 0; i < 5; i++) {
    for (l j = 0; j < 6; j++) {
      put_character(font5[c][i * 6 + j], row + i, column + j, buffer);
    }
  }
}

void output_c5(l row, l column, string& s, vs& buffer) {
  for (l i = 0; i < (l)s.size(); i++) {
    put_character_5(s[i], row, column + i * 6, buffer);
  }
}

void print_buffer(vs& buffer) {
  for (const auto& s : buffer) {
    cout << s << endl;
  }
  cout << endl
  << "------------------------------------------------------------"
  << endl << endl;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s;
  vs blank(60, string(60, '.'));
  auto buffer = blank;
  while (getline(cin, s)) {
    // cout << s << endl;
    auto cmd = to_command(s);
    switch (cmd.type) {
      case Command::EOP:
        print_buffer(buffer);
        buffer = blank;
        break;
      case Command::PRINT_C1:
        output_c1(cmd.row, cmd.column, cmd.content, buffer);
        break;
      case Command::PRINT_C5:
        output_c5(cmd.row, cmd.column, cmd.content, buffer);
        break;
      default:
        assert(false);
        break;
    }
  }
}
