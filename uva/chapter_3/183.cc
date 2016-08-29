#include <iostream>
#include <string>

using namespace std;

const int MAX = 200;

bool M[MAX][MAX];

int cols, rows;
int w;

char next_char() {
    while (true) {
        char c = getchar();
        // cerr << c << ".";
        switch (c) {
            case '1':
            case '0':
            case 'B':
            case 'D':
            case '#':
            return c;
        }
    }
    return '\n';
}

void pc(char c) {
    if (w == 50) {
        w = 0;
        putchar('\n');
    }
    putchar(c);
    w++;
}

void fill_b() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            M[r][c] = (next_char() == '1');
        }
    }
}

void fill_d(int rf, int cf, int rt, int ct) {
    if (rf == rt || cf == ct) return;
    char q = next_char();
    if (q == 'D') {
        int rm = (rf + rt + 1) / 2;
        int cm = (cf + ct + 1) / 2;
        fill_d(rf, cf, rm, cm);
        fill_d(rf, cm, rm, ct);
        fill_d(rm, cf, rt, cm);
        fill_d(rm, cm, rt, ct);
    } else {
        for (int r = rf; r < rt; r++) {
            for (int c = cf; c < ct; c++) {
                M[r][c] = (q == '1');
            }
        }
    }
}

void print_d(int rf, int cf, int rt, int ct) {
    if (rf == rt || cf == ct) return;
    bool same = true;
    for (int r = rf; r < rt && same; r++) {
        for (int c = cf; c < ct && same; c++) {
            same = (M[r][c] == M[rf][cf]);
        }
    }
    if (same) {
        pc(M[rf][cf] ? '1' : '0');
        return;
    }
    pc('D');
    int rm = (rf + rt + 1) / 2;
    int cm = (cf + ct + 1) / 2;
    print_d(rf, cf, rm, cm);
    print_d(rf, cm, rm, ct);
    print_d(rm, cf, rt, cm);
    print_d(rm, cm, rt, ct);
}

void print_b() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            pc(M[r][c] ? '1' : '0');
        }
    }
}

int main() {
    char t;
    while(t = next_char(), t != '#') {
        scanf("%d%d", &rows, &cols);
        // cerr << t << rows << cols << endl;
        w = 0;
        if (t == 'B') {
            fill_b();
            printf("D%4d%4d\n", rows, cols);
            print_d(0, 0, rows, cols);
            putchar('\n');
        } else {
            fill_d(0, 0, rows, cols);
            printf("B%4d%4d\n", rows, cols);
            print_b();
            putchar('\n');
        }
    }
    return 0;
}
