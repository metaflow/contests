#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

const int ROWS = 6;
const int COLS = 5;

string S;
int k;
using vvc = vector<vector<char>>;

vvc P;

bool backtrack(int idx) {
    if (idx == COLS) {
        k--;
        return (k == 0);
    }
    for (auto c : P[idx]) {
        S[idx] = c;
        if (backtrack(idx + 1)) return true;
    }
    return false;
}

int main() {
    int tcc;
    scanf("%d", &tcc);
    while (tcc--) {
        scanf("%d", &k);
        vvc a(COLS), b(COLS);
        for (int i = 0; i < ROWS; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < COLS; j++) {
                a[j].push_back(s[j]);
            }
        }
        for (int i = 0; i < ROWS; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < COLS; j++) {
                b[j].push_back(s[j]);
            }
        }
        for (int i = 0; i < COLS; i++) {
            sort(a[i].begin(), a[i].end());
            sort(b[i].begin(), b[i].end());
        }
        P.clear();
        P.resize(COLS);
        for (int i = 0; i < COLS; i++) {
            for (auto c : a[i]) {
                if (binary_search(b[i].begin(), b[i].end(), c) &&
                    !binary_search(P[i].begin(), P[i].end(), c)) {
                    P[i].push_back(c);
                }
            }
        }
        S = "*****";
        if (backtrack(0)) {
            cout << S << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
