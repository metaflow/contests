#include <iostream>
#include <string>

using namespace std;

int D[10], S[10];
int n;

int seq(string s) {
    int result = 0;
    for (char c : s) {
        result <<= 1;
        if (c == 'Y') result += 1;
    }
    return result;
}

bool check(int from) {
    int black = 0b1111111;
    for (int i = 0; i < n; i++) {
        int v = D[from - i] & black;
        if ((v | S[i]) != v) return false;
        black = black & ~(v ^ S[i]);
    }
    return true;
}

int main() {

    D[0] = seq("YYYYYYN");
    D[1] = seq("NYYNNNN");
    D[2] = seq("YYNYYNY");
    D[3] = seq("YYYYNNY");
    D[4] = seq("NYYNNYY");
    D[5] = seq("YNYYNYY");
    D[6] = seq("YNYYYYY");
    D[7] = seq("YYYNNNN");
    D[8] = seq("YYYYYYY");
    D[9] = seq("YYYYNYY");

    while(scanf("%d", &n), n != 0) {
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            S[i] = seq(s);
        }
        bool f = false;
        for (int i = n - 1; i <= 9 && (!f); i++) {
            f = f || check(i);
        }
        if (f) {
            printf("MATCH\n");
        } else {
            printf("MISMATCH\n");
        }
    }
    return 0;
}
