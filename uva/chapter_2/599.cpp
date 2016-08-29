#include <stdio.h>
#include <bitset>

using namespace std;

const int MAX = 26;

char get_token() {
    char c;
    while (scanf("%c", &c)) {
        if ((c >= 'A' && c <= 'Z') || (c == '*')) return c;
    }
    return 0;
}

int main() {
    int cc;
    scanf("%d", &cc);
    while (cc--) {
        char a;
        bitset<MAX> connected;
        int edge_count = 0;
        while (true) {
            a = get_token();
            if (a == '*') break;
            connected.set(a - 'A');
            connected.set(get_token() - 'A');
            edge_count++;
        }
        char s[250];
        fgets(s, 250, stdin); // skip asteriks
        fgets(s, 250, stdin);
        int acorn_count = 0;
        int vertex_count = 0;
        for (int i = 0; s[i]; i++) {
            if (s[i] < 'A' || s[i] > 'Z') continue;
            vertex_count++;
            if (!connected[s[i] - 'A']) acorn_count++;
        }
        int tree_count = vertex_count - edge_count - acorn_count;
        printf("There are %d tree(s) and %d acorn(s).\n", tree_count, acorn_count);
    }
    return 0;
}
