#include <bitset>
#include <string>
#include <iostream>

using namespace std;

int board[15]; // [column]
long long count;
int n;
int full;

void backtrack(int r, int d1, int d2, int c) {
    if (r == full) {
        count++;
        return;
    }

    int pos = full & ~(r | d1 | d2 | board[c]);

    while (pos) {
        int p = pos & -pos;
        pos -= p;
        backtrack(r | p, (d1 | p) >> 1, (d2 | p) << 1, c + 1);
    }
}

int main() {
    int tc = 0;
    while (cin >> n, n != 0) {
        tc++;
        string s;
        count = 0;
        getline(cin, s);
        for (int i = 0; i < n; i++) {
            board[i] = 0;
            getline(cin, s);
            for (int j = 0; j < s.size(); j++) {
                if (s[j] == '*') board[i] |= 1 << j;
            }
        }
        full = (1 << n) - 1;
        backtrack(0, 0, 0, 0);

        printf("Case %d: %lld\n", tc, count);
    }
    return 0;
}
