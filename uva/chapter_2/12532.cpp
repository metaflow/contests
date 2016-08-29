#include <vector>
#include <stdio.h>

using namespace std;

struct sign {
    bool positive;
    bool zero;
    bool operator==(const sign& a)
    {
        if (zero != a.zero) return false;
        return zero || (positive == a.positive);
    }
};

typedef vector<sign> vs;

#define LEFT(d) (d << 1)
#define RIGHT(d) ((d << 1) + 1)

vs list, tree;
sign one;

sign sign_of(int v) {
    sign r;
    r.zero = v == 0;
    r.positive = v > 0;
    return r;
}

sign product_sign(sign a, sign b) {
    sign r;
    r.zero = a.zero || b.zero;
    r.positive = a.positive == b.positive;
    return r;
}

void init(int d, int f, int t) {
    if (f == t) {
        tree[d] = list[f];
        return;
    }
    int m = (f + t) / 2;
    init(LEFT(d), f, m);
    init(RIGHT(d), m + 1, t);
    tree[d] = product_sign(tree[LEFT(d)], tree[RIGHT(d)]);
}

void update(int d, int f, int t, int i) {
    if (f > i || t < i) return;
    if (f == t) {
        tree[d] = list[f];
        return;
    }
    int m = (f + t) / 2;
    update(LEFT(d), f, m, i);
    update(RIGHT(d), m + 1, t, i);
    tree[d] = product_sign(tree[LEFT(d)], tree[RIGHT(d)]);
}

sign product_tree(int d, int f, int t, int l, int r) {
    if (l > t || r < f) return one;
    if (l <= f && t <= r) return tree[d];
    int m = (f + t) / 2;
    sign a = product_tree(LEFT(d), f, m, l, r);
    if (a.zero) return a;
    sign b = product_tree(RIGHT(d), m + 1, t, l, r);
    return product_sign(a, b);
}

sign product(int f, int t) {
    // printf("product %d %d\n", f, t);
    return product_tree(1, 0, list.size() - 1, f, t);
}

void change(int i, int v) {
    // printf("change %d %d\n", i, v);
    sign s = sign_of(v);
    if (s == list[i]) return;
    list[i] = s;
    update(1, 0, list.size() - 1, i);
}

void print_sign(const sign& s) {
    if (s.zero) {
        printf("0");
    } else {
        printf("%c", (s.positive ? '+' : '-'));
    }
}

void print_list() {
    for (int i = 0; i < list.size(); i++) print_sign(list[i]);
    printf("\n");
}

int main() {
    int n, k;
    one.zero = false;
    one.positive = true;
    while (scanf("%d %d", &n, &k) != EOF) {
        list.clear();
        tree.clear();
        while (n--) {
            int v;
            scanf("%d", &v);
            list.push_back(sign_of(v));
        }
        tree.resize(list.size() * 4);
        // print_list();
        init(1, 0, list.size() - 1);
        while (k--) {
            char op[8];
            int i, j;
            scanf("%s %d %d", op, &i, &j);
            switch(op[0]) {
                case 'C': change(i - 1, j);
                    // print_list();
                    break;
                case 'P': print_sign(product(i - 1, j - 1)); break;
            }
        }
        printf("\n");
    }
}
