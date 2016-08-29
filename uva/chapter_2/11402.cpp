#include <stdio.h>
#include <iostream>

using namespace std;

#define LEFT(p) (p << 1)
#define RIGHT(p) ((p << 1) + 1)

struct node {
    char op;
    int l, r, v;
};

const int N = 1024000;
node nodes[N * 4 + 1];
char pirates[N];

void init(int p, int left, int right) {
    node &n = nodes[p];
    n.l = left;
    n.r = right;

    n.op = ' ';
    if (n.l == n.r) {
        n.v = pirates[n.l];
    } else {
        int m = (n.l + n.r) / 2;
        init(LEFT(p), n.l, m);
        init(RIGHT(p), m + 1, n.r);
        n.v = nodes[LEFT(p)].v + nodes[RIGHT(p)].v;
    }
}

void set_op(int p, char op) {
    node &n = nodes[p];
    if (op == 'I') {
        switch (n.op) {
            case 'I': n.op = ' '; return;
            case 'F': n.op = 'E'; return;
            case ' ': n.op = 'I'; return;
            case 'E': n.op = 'F'; return;
        }
    }
    n.op = op;
}

void calc(int p) {
    node &n = nodes[p];
    if (n.op == ' ') return;
    switch (n.op) {
        case 'F': n.v = n.r - n.l + 1; break;
        case 'E': n.v = 0; break;
        case 'I': n.v = n.r - n.l + 1 - n.v; break;
    }
    set_op(LEFT(p), n.op);
    set_op(RIGHT(p), n.op);
    n.op = ' ';
    // cerr << n.l << ".." << n.r << "=" << n.v << "\n";
}

void update(int p, int left, int right, char op) {
    node &n = nodes[p];
    if (left <= n.l && n.r <= right) set_op(p, op);
    calc(p);
    if (right < n.l || n.r < left) return;
    if (left <= n.l && n.r <= right) return;
    update(LEFT(p), left, right, op);
    update(RIGHT(p), left, right, op);
    n.v = nodes[LEFT(p)].v + nodes[RIGHT(p)].v;
}

int query(int p, int left, int right) {
    node &n = nodes[p];
    calc(p);
    if (right < n.l || n.r < left) return 0;
    if (left <= n.l && n.r <= right) return n.v;
    int r = query(LEFT(p), left, right) + query(RIGHT(p), left, right);
    n.v = nodes[LEFT(p)].v + nodes[RIGHT(p)].v;
    return r;
}

int main() {
    int tc;
    scanf("%d", &tc);
    for (int i = 0; i < tc; i++) {
        printf("Case %d:\n", i + 1);
        int desc;
        scanf("%d", &desc);
        int p = 0;
        while (desc--) {
            char s[80];
            int c;
            scanf("%d %s", &c, s);
            int j = 0;
            while (s[j]) s[j++] -= '0';
            while (c--) for (int l = 0; l < j; l++) pirates[p++] = s[l];
        }
        init(1, 0, p-1);
        int k;
        scanf("%d", &k);
        int q = 0;
        while(k--) {
            char op;
            int a, b;
            scanf(" %c %d %d", &op, &a, &b);
            // cerr << op << " " << a << ".." << b << "\n";
            if (op == 'S') {
                int r = query(1, a, b);
                printf("Q%d: %d\n", ++q, r);
            } else {
                update(1, a, b, op);
            }
        }
    }
    return 0;
}
