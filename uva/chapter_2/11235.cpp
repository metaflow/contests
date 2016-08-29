#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

#define LEFT(i) (i * 2)
#define RIGHT(i) (i * 2 + 1)

struct node {
    int count;
    int from, to;
};

typedef vector<node> vn;

vn node_list, node_tree;

void add_node(int from, int to) {
    node n;
    n.from = from;
    n.to = to;
    n.count = n.to - n.from + 1;
    node_list.push_back(n);
}

void init_subtree(int d, int index_from, int index_to) {
    if (index_from == index_to) {
        node_tree[d] = node_list[index_from];
        return;
    }
    int m = (index_from + index_to) / 2;
    init_subtree(LEFT(d), index_from, m);
    init_subtree(RIGHT(d), m + 1, index_to);
    node &n = node_tree[d];
    node l = node_tree[LEFT(d)];
    node r = node_tree[RIGHT(d)];
    n.from = l.from;
    n.to = r.to;
    n.count = max(l.count, r.count);
}

void init_tree() {
    node_tree.resize(node_list.size() * 4);
    init_subtree(1, 0, node_list.size() - 1);
}

int query_subtree(int d, int index_from, int index_to, int from, int to) {
    node &n = node_tree[d];
    if (n.to < from || n.from > to) return 0;
    if (from <= n.from && n.to <= to) return n.count;
    if (index_from == index_to) {
        from = max(from, n.from);
        to = min(to, n.to);
        return to - from + 1;
    }
    int m = (index_from + index_to) / 2;
    int l = query_subtree(LEFT(d), index_from, m, from, to);
    int r = query_subtree(RIGHT(d), m + 1, index_to, from, to);
    return max(l, r);
}

int query(int from, int to) {
    return query_subtree(1, 0, node_list.size() - 1, from, to);
}

int main() {
    int n, q;
    while (scanf("%d", &n), n) {
        node_list.clear();
        node_tree.clear();
        scanf("%d", &q);
        int last = -1000000;
        int from = -1;
        for (int i = 0; i < n; i++) {
            int v;
            scanf("%d", &v);
            if (v == last) continue;
            if (i) add_node(from, i - 1);
            last = v;
            from = i;
        }
        add_node(from, n - 1);
        init_tree();
        while (q--) {
            int i, j;
            scanf("%d %d", &i, &j);
            i--; j--;
            printf("%d\n", query(i, j));
        }
    }
    return 0;
}
