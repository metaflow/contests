#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;

struct cell {
    ll value;
    int ref_count;
    vector<ii> formula, dependent;
};

using sheet = vector<vector<cell>>;

void add_formula(sheet &s, int r, int c, int ref_r, int ref_c) {
    s[r][c].ref_count++;
    s[r][c].formula.push_back(make_pair(ref_r, ref_c));
    s[ref_r][ref_c].dependent.push_back(make_pair(r, c));
}

void read_cell(sheet &s, int r, int c) {
    cell &x = s[r][c];
    x.value = 0;
    x.ref_count = 0;
    bool negative = false;
    int state = 0;
    int ref_r = 0;
    int ref_c = 0;
    while (true) {
        char t = getchar();
        switch (t) {
            case ' ':
            case '\n':
            case '\0':
                if (state == 0) {
                    if (t == '\0') return;
                    break;
                }
                if (state == 2) {
                    add_formula(s, r, c, ref_r - 1, ref_c - 1);
                }
                if (state == 1 && negative) {
                    x.value = -x.value;
                }
                return;
            case '=':
                state = 2;
                break;
            case '+':
                add_formula(s, r, c, ref_r - 1, ref_c - 1);
                ref_r = 0;
                ref_c = 0;
                break;
            case '-':
                negative = true;
                break;
            default:
                if (isdigit(t)) {
                    if (state == 0 || state == 1) {
                        state = 1;
                        x.value = x.value * 10 + (t - '0');
                    } else {
                        ref_r = ref_r * 10 + (t - '0');
                    }
                }
                if (isalpha(t)) {
                    ref_c = ref_c * ('Z' - 'A' + 1) + (t - 'A' + 1);
                }
                break;
        }
    }
}

int main() {
    int tcc;
    cin >> tcc;
    while (tcc--) {
        int cols, rows;
        cin >> cols >> rows;
        sheet s(rows);
        for (int r = 0; r < rows; r++) {
            s[r].resize(cols);
        }
        stack<ii> q;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                read_cell(s, r, c);
                if (s[r][c].ref_count == 0) {
                    q.push(make_pair(r, c));
                }
            }
        }

        while (!q.empty()) {
            ii pos = q.top();
            q.pop();
            cell &x = s[pos.first][pos.second];
            if (!x.formula.empty()) {
                x.value = 0;
                for (auto c : x.formula) {
                    x.value += s[c.first][c.second].value;
                }
            }
            for (auto c : x.dependent) {
                s[c.first][c.second].ref_count--;
                if (s[c.first][c.second].ref_count == 0) {
                    q.push(c);
                }
            }
        }

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (c) cout << ' ';
                cout << s[r][c].value;
            }
            cout << endl;
        }
    }
}
