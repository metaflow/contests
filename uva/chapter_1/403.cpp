#include <iostream>
#include <string>

using namespace std;

const int SIZE = 60;

int px, py;

char page[SIZE][SIZE];

char c5[][7] = {
  ".***..",
"*...*.",
"*****.",
"*...*.",
"*...*.",
"****..",
"*...*.",
"****..",
"*...*.",
"****..",
".****.",
"*...*.",
"*.....",
"*.....",
".****.",
"****..",
"*...*.",
"*...*.",
"*...*.",
"****..",
"*****.",
"*.....",
"***...",
"*.....",
"*****.",
"*****.",
"*.....",
"***...",
"*.....",
"*.....",
".****.",
"*.....",
"*..**.",
"*...*.",
".***..",
"*...*.",
"*...*.",
"*****.",
"*...*.",
"*...*.",
"*****.",
"..*...",
"..*...",
"..*...",
"*****.",
"..***.",
"...*..",
"...*..",
"*..*..",
".**...",
"*...*.",
"*..*..",
"***...",
"*..*..",
"*...*.",
"*.....",
"*.....",
"*.....",
"*.....",
"*****.",
"*...*.",
"**.**.",
"*.*.*.",
"*...*.",
"*...*.",
"*...*.",
"**..*.",
"*.*.*.",
"*..**.",
"*...*.",
".***..",
"*...*.",
"*...*.",
"*...*.",
".***..",
"****..",
"*...*.",
"****..",
"*.....",
"*.....",
".***..",
"*...*.",
"*...*.",
"*..**.",
".****.",
"****..",
"*...*.",
"****..",
"*..*..",
"*...*.",
".****.",
"*.....",
".***..",
"....*.",
"****..",
"*****.",
"*.*.*.",
"..*...",
"..*...",
".***..",
"*...*.",
"*...*.",
"*...*.",
"*...*.",
".***..",
"*...*.",
"*...*.",
".*.*..",
".*.*..",
"..*...",
"*...*.",
"*...*.",
"*.*.*.",
"**.**.",
"*...*.",
"*...*.",
".*.*..",
"..*...",
".*.*..",
"*...*.",
"*...*.",
".*.*..",
"..*...",
"..*...",
"..*...",
"*****.",
"...*..",
"..*...",
".*....",
"*****."
};

void set_position(int x, int y) {
  px = x;
  py = y;
}

int font_width(string font) {
  return font[1] == '1' ? 1 : 6;
}

string parse_content(string s) {
  int a = s.find('|');
  int b = s.rfind('|');
  return s.substr(a, b - a + 1);
}

int get_width(string font, string content) {
  return content.length() * font_width(font);
}

void set(int x, int y, char c) {
  if (c == ' ') return;
  if (x < 1 || x > SIZE || y < 1 || y > SIZE) return;
  page[x - 1][y - 1] = c;
}

void print_c5_letter(char c) {
  if (c < 'A' || c > 'Z') return;
  int k = 5 * (c - 'A');
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 6; j++) {
      set(px + j, py + i, c5[k + i][j]);
    }
  }
}

void print_c1_letter(char c) {
  set(px, py, c);  
}

void print_letter(string font, char c) {
  if (font_width(font) == 1) {    
    print_c1_letter(c);
  } else {
    print_c5_letter(c);
  }
}

void print_content(string font, string content) {
  int w = font_width(font);
  for (int i = 0; i < content.length(); i++) {
    print_letter(font, content[i]);
    set_position(px + w, py);
  }
}

void cmd_p(int x, int y, string font, string content) {
  set_position(x - 1, y - 1);
  print_content(font, content);
}

void cmd_l(int y, string font, string content) {
  set_position(1, y);
  print_content(font, content);
}

void cmd_r(int y, string font, string content) {
  int w = get_width(font, content);
  set_position(SIZE - w + 1, y);
  print_content(font, content);
}

void cmd_c(int y, string font, string content) {
  int w = get_width(font, content);
  set_position(SIZE / 2 + 1 - w / 2, y);
  print_content(font, content);
}

void clear() {
  for (int i = 1; i <= SIZE; i++) for (int j = 1; j < SIZE; j++) {
    set(i, j, '.');
  }
}

void print_page() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      cout << page[i][j];
    }
    cout << "\n";
  }
  cout << "\n------------------------------------------------------------\n";
}

int main() {
    string cmd;
    clear();
    while (cin >> cmd) {
      string font;
      int x, y;
      string content;
      switch(cmd[1]) {
        case 'P':
          cin >> font >> x >> y;
          getline(cin, content);
          cmd_p(x, y, font, parse_content(content));
          break;
        case 'L':
          cin >> font >> y;
          getline(cin, content);
          cmd_l(y, font, parse_content(content));
          break;
        case 'R':
          cin >> font >> y;
          getline(cin, content);
          cmd_r(y, font, parse_content(content));
          break;
        case 'C':
          cin >> font >> y;
          getline(cin, content);
          cmd_c(y, font, parse_content(content));
          break;
        case 'E':
          print_page();
          clear();
          break;
      }
    }
}